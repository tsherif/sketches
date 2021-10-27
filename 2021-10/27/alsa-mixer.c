#include <alsa/asoundlib.h>
#include "../../lib/utils.h"
#include "../../lib/linux-utils.h"

#define SAMPLE_MAX 32767
#define SAMPLE_MIN (-32768)

#define MIX_CHANNELS 32
#define MIX_BUFFER_FRAMES 2048

typedef struct {
    int16_t* data;
    int32_t count;
    int32_t cursor;
} AudioStream;

struct {
    AudioStream channels[32];
    int32_t count;
} mixer;

void mixSounds(int16_t* dst, int16_t* src, int32_t numFrames) {
    for (int32_t i = 0; i < numFrames * 2; ++i) {
        int32_t sample = dst[i] + src[i];
        if (sample > SAMPLE_MAX) {
            sample = SAMPLE_MAX;
        }
        if (sample < SAMPLE_MIN) {
            sample = SAMPLE_MIN;
        }

        dst[i] = sample;
    }
}

void play(Buffer* buffer) {
    if (mixer.count == MIX_CHANNELS) {
        return;
    }

    mixer.channels[mixer.count].data = (int16_t *) buffer->data;
    mixer.channels[mixer.count].count = buffer->size / 2;
    mixer.channels[mixer.count].cursor = 0;

    ++mixer.count;
}

void stop(int32_t i) {
    if (i >= mixer.count) {
        return;
    }

    int32_t last = mixer.count - 1;

    mixer.channels[i].data = mixer.channels[last].data;
    mixer.channels[i].count = mixer.channels[last].count;
    mixer.channels[i].cursor = mixer.channels[last].cursor;

    --mixer.count;
}

bool audioCallback(int16_t* mixBuffer, int32_t numFrames) {
    int32_t numSamples = numFrames * 2;

    for (int32_t i = 0; i < numSamples; ++i) {
        mixBuffer[i] = 0;
    }    

    if (mixer.count == 0) {
        return false;
    }


    for (int32_t i = 0; i < mixer.count; ++i) {
        AudioStream* channel = mixer.channels + i;
        int32_t samplesToMix = numSamples;
        int32_t samplesRemaining = channel->count - channel->cursor;

        if (samplesRemaining < numSamples) {
            samplesToMix = samplesRemaining;
        }

        for (int32_t i = 0; i < samplesToMix; ++i) {
            int32_t sample = mixBuffer[i] + channel->data[channel->cursor];
            
            if (sample < SAMPLE_MIN) {
                sample = SAMPLE_MIN;
            }

            if (sample > SAMPLE_MAX) {
                sample = SAMPLE_MAX;
            }

            mixBuffer[i] = sample;
            ++channel->cursor;
        }
    }

    for (int32_t i = mixer.count - 1; i >= 0; --i) {
        AudioStream* channel = mixer.channels + i;
        if (channel->cursor == channel->count) {
            stop(i);
        }
    }
}

int main(void) {
    
    Buffer musicFile;
    Buffer musicData;

    if (!loadBinFile("../../audio/music.wav", &musicFile)) {
        debugLog("Could not open music file.");
        return 1;    
    }
    
    if (!wavToSound(&musicFile, &musicData)) {
        debugLog("Could not parse music file.");
        return 1;    
    }

    Buffer jumpFile;
    Buffer jumpData;

    if (!loadBinFile("../../audio/jump.wav", &jumpFile)) {
        debugLog("Could not open sound file.");
        return 1;    
    }
    
    if (!wavToSound(&jumpFile, &jumpData)) {
        debugLog("Could not parse sound file.");
        return 1;    
    }

    play(&musicData);

    snd_pcm_t* device = 0;
    snd_pcm_hw_params_t *deviceParams = 0;

    if (snd_pcm_open(&device, "default", SND_PCM_STREAM_PLAYBACK, 0) < 0) {
        debugLog("Could not open audio device.");
        return 1;
    }

    snd_pcm_hw_params_alloca(&deviceParams);
    snd_pcm_hw_params_any(device, deviceParams);

    if (snd_pcm_hw_params_set_access(device, deviceParams, SND_PCM_ACCESS_RW_INTERLEAVED) < 0) {
        debugLog("Could not set access.");
        return 1;   
    }

    if (snd_pcm_hw_params_set_format(device, deviceParams, SND_PCM_FORMAT_S16_LE) < 0) {
        debugLog("Could not set format.");
        return 1;   
    }

    if (snd_pcm_hw_params_set_rate(device, deviceParams, 44100, 0) < 0) {
        debugLog("Could not set rate.");
        return 1;   
    }

    if (snd_pcm_hw_params_set_channels(device, deviceParams, 2) < 0) {
        debugLog("Could not set rate.");
        return 1;   
    }

    if (snd_pcm_hw_params(device, deviceParams) < 0) {
        debugLog("Could not set device params.");
        return 1;   
    }

    int16_t mixBuffer[MIX_BUFFER_FRAMES * 2];

    int32_t tick = 0;
    while (audioCallback(mixBuffer, MIX_BUFFER_FRAMES)) {
        if (snd_pcm_writei(device, mixBuffer, MIX_BUFFER_FRAMES) < 0) {
            debugLog("Could not play audio.");
            return 1;
        }

        if (tick == 50) {
            play(&jumpData);
            tick = 0;
        }

        ++tick;
    }

    snd_pcm_drain(device);

    return 0;
}
 
