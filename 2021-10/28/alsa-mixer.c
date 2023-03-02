#include <alsa/asoundlib.h>
#include <pthread.h>
#include "../../lib/c/utils.h"
#include "../../lib/c/linux-utils.h"

#define SAMPLE_MAX 32767
#define SAMPLE_MIN (-32768)

#define MIX_CHANNELS 32
#define MIX_BUFFER_FRAMES 2048

pthread_t audioThreadHandle;
pthread_mutex_t mixerLock;


Buffer musicFile;
Buffer musicData;
Buffer jumpFile;
Buffer jumpData;

typedef struct {
    int16_t* data;
    int32_t count;
    int32_t cursor;
} AudioStream;

struct {
    AudioStream channels[32];
    int32_t count;
} mixer;

void play(Buffer* buffer) {
    pthread_mutex_lock(&mixerLock);

    if (mixer.count == MIX_CHANNELS) {
        return;
    }

    mixer.channels[mixer.count].data = (int16_t *) buffer->data;
    mixer.channels[mixer.count].count = buffer->size / 2;
    mixer.channels[mixer.count].cursor = 0;

    ++mixer.count;

    pthread_mutex_unlock(&mixerLock); 
}

void *audioThread(void* args) {
    snd_pcm_t* device = (snd_pcm_t*) args;
    int16_t mixBuffer[MIX_BUFFER_FRAMES * 2];

    int32_t tick = 0;
    while (true) {

        int32_t numSamples = MIX_BUFFER_FRAMES * 2;

        for (int32_t i = 0; i < numSamples; ++i) {
            mixBuffer[i] = 0;
        }    

        pthread_mutex_lock(&mixerLock);

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


        int32_t last = mixer.count - 1;
        for (int32_t i = mixer.count - 1; i >= 0; --i) {
            AudioStream* channel = mixer.channels + i;
            if (channel->cursor == channel->count) {

                mixer.channels[i].data = mixer.channels[last].data;
                mixer.channels[i].count = mixer.channels[last].count;
                mixer.channels[i].cursor = mixer.channels[last].cursor;

                --mixer.count;
            }
        }

        pthread_mutex_unlock(&mixerLock); 
        
        if (snd_pcm_writei(device, mixBuffer, MIX_BUFFER_FRAMES) < 0) {
            if (snd_pcm_prepare(device) < 0) {
                debugLog("Could not play audio.");
            } 
        }

        if (tick == 50) {
            play(&jumpData);
            tick = 0;
        }

        ++tick;
    }
}

int main(void) {
    if (!loadBinFile("../../audio/music.wav", &musicFile)) {
        debugLog("Could not open music file.");
        return 1;    
    }
    
    if (!wavToSound(&musicFile, &musicData)) {
        debugLog("Could not parse music file.");
        return 1;    
    }

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

    pthread_mutex_init(&mixerLock, NULL);
    pthread_create(&audioThreadHandle, NULL, audioThread, device);

    while (true) {}

    return 0;
}
 
