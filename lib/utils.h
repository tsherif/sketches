#ifndef UTILS
#define UTILS

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint8_t* data;
    uint32_t size;
} Buffer;

// TODO(Tarek): Check format. Should be 2-channel 44.1kHz
bool wavToSound(Buffer* soundData, Buffer* sound) {
    int32_t offset = 0;
    uint32_t chunkType = 0;
    uint32_t chunkSize = 0;
    uint32_t fileFormat = 0;

    chunkType = *(uint32_t *) soundData->data;
    offset +=  2 * sizeof(uint32_t);

    if (chunkType != 0x46464952) { // "RIFF" little-endian
        return false;
    }

    fileFormat = *(uint32_t *) (soundData->data + offset);
    offset += sizeof(uint32_t);

    if (fileFormat != 0x45564157) { // "WAVE" little-endian
        return false;
    }

    while (offset + 2 * sizeof(uint32_t) < soundData->size) {
        chunkType = *(uint32_t *) (soundData->data + offset);
        offset +=  sizeof(uint32_t);

        chunkSize = *(uint32_t *) (soundData->data + offset);
        offset +=  sizeof(uint32_t);

        if (offset + chunkSize > soundData->size) {
            return false;
        }

        if (chunkType == 0x61746164) { // "data" little-endian
            sound->size = chunkSize;
            sound->data = (uint8_t *) malloc(chunkSize);
            memcpy(sound->data, soundData->data + offset, chunkSize);
            break;
        }

        offset += chunkSize;
    }

    return true;
}

#endif
