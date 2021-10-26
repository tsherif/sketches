#include <alsa/asoundlib.h>
#include "../../lib/utils.h"
#include "../../lib/linux-utils.h"
 
int main(void) {
    
    Buffer musicFile;
    Buffer musicData;

    if (!loadBinFile("../../audio/music.wav", &musicFile)) {
        debugLog("Could not open sound file.");
        return 1;    
    }
    
    if (!wavToSound(&musicFile, &musicData)) {
        debugLog("Could not parse sound file.");
        return 1;    
    }

    uint32_t numFrames = musicData.size / 4;

    snd_pcm_t* device;

    if (snd_pcm_open(&device, "default", SND_PCM_STREAM_PLAYBACK, 0) < 0) {
        debugLog("Could not open audio device.");
        return 1;
    }

    if (snd_pcm_set_params(device, SND_PCM_FORMAT_S16_LE, SND_PCM_ACCESS_RW_INTERLEAVED, 2, 44100, 1, 50000) < 0) {
        debugLog("Could not set audio params.");
        return 1;   
    }

    if (snd_pcm_writei(device, musicData.data, numFrames) < 0) {
        debugLog("Could not play audio.");
        return 1;
    }

    return 0;
}
 
