// Must be implemented by platform layer, to be used by platform game.

typedef struct Sound Sound;
Sound* loadSound(const char* fileName);
void playSound(Sound* sound);
