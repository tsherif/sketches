#ifndef _PLATFORM_H_
#define _PLATFORM_H_
#include <stdbool.h>

// Must be implemented by platform layer, to be used by platform game.
typedef struct PlatformSound PlatformSound;
bool platform_initAudio(void);
PlatformSound* platform_loadSound(const char* fileName);
void platform_playSound(PlatformSound* sound);

#endif