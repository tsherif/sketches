#include <alsa/asoundlib.h>
#include "../../lib/utils.h"
#include "../../lib/linux-utils.h"

#define SAMPLE_MAX 32767
#define SAMPLE_MIN (-32768)

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

    uint32_t numMusicFrame = musicData.size / 4;
    uint32_t numJumpFrame = jumpData.size / 4;

    mixSounds((int16_t*)(musicData.data + 4 * 44000), (int16_t*) jumpData.data, numJumpFrame);

    snd_pcm_t* device;

    if (snd_pcm_open(&device, "default", SND_PCM_STREAM_PLAYBACK, 0) < 0) {
        debugLog("Could not open audio device.");
        return 1;
    }

    if (snd_pcm_set_params(device, SND_PCM_FORMAT_S16_LE, SND_PCM_ACCESS_RW_INTERLEAVED, 2, 44100, 1, 50000) < 0) {
        debugLog("Could not set audio params.");
        return 1;   
    }

    if (snd_pcm_writei(device, musicData.data, numMusicFrame) < 0) {
        debugLog("Could not play audio.");
        return 1;
    }

    return 0;
}
 
