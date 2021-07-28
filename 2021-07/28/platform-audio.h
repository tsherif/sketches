#ifndef _PLATFORM_AUDIO_H_
#define _PLATFORM_AUDIO_H_
#include <stdbool.h>

// Must be implemented by platform layer, to be used by platform game.
typedef struct Sound Sound;
bool initAudio(void);
Sound* loadSound(const char* fileName);
void playSound(Sound* sound);

#endif