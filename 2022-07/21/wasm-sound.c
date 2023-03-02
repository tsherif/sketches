#include <emscripten/emscripten.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <stdio.h>

#include "../../lib/c/utils.h"
#include "../../lib/c/linux-utils.h"

int main() {
    Buffer musicFile = { 0 };
    Buffer musicData = { 0 };

    if (!loadBinFile("./audio/music.wav", &musicFile)) {
        fprintf(stderr, "Could not open music file.\n");
        return 1;    
    }
    
    if (!wavToSound(&musicFile, &musicData)) {
        fprintf(stderr, "Could not parse music file.\n");
        return 1;    
    }

    ALCdevice *device = alcOpenDevice(NULL);
    ALCcontext *ctx = alcCreateContext(device, NULL);
    alcMakeContextCurrent(ctx);
    
    ALuint buffer = 0;
    alGenBuffers(1, &buffer);
    alBufferData(buffer, AL_FORMAT_STEREO16, musicData.data, musicData.size, 44100);

    ALuint source = 0;
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);

    alSourcePlay(source);

    return 0;
}