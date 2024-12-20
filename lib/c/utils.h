#ifndef UTILS
#define UTILS

#include <stdbool.h>
#include <stdint.h>
#include <malloc.h>
#include <string.h>

typedef struct {
    union {
        void* data;
        uint8_t* u8data;
        char* cdata;
    };
    uint32_t size;
} DataBuffer;

typedef struct {
    uint8_t* data;
    int32_t width;
    int32_t height;
    int32_t channels;
} Image;

// TODO(Tarek): Check format. Should be 2-channel 44.1kHz
bool wavToSound(DataBuffer* soundData, DataBuffer* sound) {
    int32_t offset = 0;
    uint32_t chunkType = 0;
    uint32_t chunkSize = 0;
    uint32_t fileFormat = 0;

    chunkType = *(uint32_t *) soundData->u8data;
    offset +=  2 * sizeof(uint32_t);

    if (chunkType != 0x46464952) { // "RIFF" little-endian
        return false;
    }

    fileFormat = *(uint32_t *) (soundData->u8data + offset);
    offset += sizeof(uint32_t);

    if (fileFormat != 0x45564157) { // "WAVE" little-endian
        return false;
    }

    while (offset + 2 * sizeof(uint32_t) < soundData->size) {
        chunkType = *(uint32_t *) (soundData->u8data + offset);
        offset +=  sizeof(uint32_t);

        chunkSize = *(uint32_t *) (soundData->u8data + offset);
        offset +=  sizeof(uint32_t);

        if (offset + chunkSize > soundData->size) {
            return false;
        }

        if (chunkType == 0x61746164) { // "data" little-endian
            sound->size = chunkSize;
            sound->data = (uint8_t *) malloc(chunkSize);
            memcpy(sound->data, soundData->u8data + offset, chunkSize);
            break;
        }

        offset += chunkSize;
    }

    return true;
}

bool strEquals(const char* s1, const char* s2, int32_t n) {
    for (int32_t i = 0; i < n; ++i) {
        if (s1[i] != s2[i]) {
            return false;
        }

        if (s1[i] == '\0' || s2[i] == '\0') {
            return s1[i] == '\0' && s2[i] == '\0';
        }
    }

    return true;
}

float clamp(float value, float min, float max) {
    if (value < min) {
        return min;
    }

    if (value > max) {
        return max;
    }

    return value;
}

#endif
