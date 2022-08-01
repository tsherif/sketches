#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <stdio.h>

#include "../../lib/utils.h"
#include "../../lib/linux-utils.h"

ALCdevice *device;
ALCcontext *ctx;
ALuint buffers[2];
ALuint sources[2];

Buffer musicFile = { 0 };
Buffer musicData = { 0 };
Buffer jumpFile = { 0 };
Buffer jumpData = { 0 };

EM_BOOL onKeyDown(int eventType, const EmscriptenKeyboardEvent *keyEvent, void *userData) {
    alBufferData(buffers[1], AL_FORMAT_STEREO16, jumpData.data, jumpData.size, 44100);
    alSourcePlay(sources[1]);

    return EM_TRUE;
}

int main() {

    if (!loadBinFile("./audio/music.wav", &musicFile)) {
        fprintf(stderr, "Could not open music file.\n");
        return 1;    
    }
    
    if (!wavToSound(&musicFile, &musicData)) {
        fprintf(stderr, "Could not parse music file.\n");
        return 1;    
    }

    if (!loadBinFile("./audio/jump.wav", &jumpFile)) {
        fprintf(stderr, "Could not open jump file.\n");
        return 1;    
    }
    
    if (!wavToSound(&jumpFile, &jumpData)) {
        fprintf(stderr, "Could not parse jump file.\n");
        return 1;    
    }

    device = alcOpenDevice(NULL);
    ctx = alcCreateContext(device, NULL);
    alcMakeContextCurrent(ctx);
    
    alGenBuffers(2, buffers);
    alBufferData(buffers[0], AL_FORMAT_STEREO16, musicData.data, musicData.size, 44100);

    alGenSources(2, sources);
    alSourcei(sources[0], AL_BUFFER, buffers[0]);
    alSourcei(sources[1], AL_BUFFER, buffers[1]);

    alSourcePlay(sources[0]);

    emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, NULL, EM_FALSE, onKeyDown);

    return 0;
}