#ifndef UTILS
#define UTILS

#include <stdbool.h>
#include <stdint.h>
#include <malloc.h>
#include <string.h>

typedef struct {
    uint8_t* data;
    uint32_t size;
} Buffer;

typedef struct {
    uint8_t* data;
    int32_t width;
    int32_t height;
    int32_t channels;
} Image;

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

typedef struct {
    float* positions; 
    float* normals; 
    float* uvs; 
    uint16_t* indices;
    int32_t vertexCount;
    int32_t elementCount;
} BasicMesh;

void createSphere(BasicMesh* mesh) {
    int32_t longBands = 32;
    int32_t latBands = 32;
    float latStep = (float) M_PI / latBands;
    float longStep = 2.0f * (float) M_PI / longBands;
    mesh->vertexCount = longBands * latBands * 4;
    mesh->elementCount = longBands * latBands * 6;
    mesh->positions = malloc(mesh->vertexCount * 3 * sizeof(float));
    mesh->normals = malloc(mesh->vertexCount * 3 * sizeof(float));
    mesh->uvs = malloc(mesh->vertexCount * 2 * sizeof(float));
    mesh->indices = malloc(mesh->elementCount * sizeof(uint16_t));
    uint16_t k = 0; 
    int32_t l = 0;
    
    for (int32_t i = 0; i < latBands; i++) {
        float latAngle = i * latStep;
        float y1 = cosf(latAngle);
        float y2 = cosf(latAngle + latStep);
        for (int32_t j = 0; j < longBands; j++) {
            float longAngle = j * longStep;
            float x1 = sinf(latAngle) * cosf(longAngle);
            float x2 = sinf(latAngle) * cosf(longAngle + longStep);
            float x3 = sinf(latAngle + latStep) * cosf(longAngle);
            float x4 = sinf(latAngle + latStep) * cosf(longAngle + longStep);
            float z1 = sinf(latAngle) * sinf(longAngle);
            float z2 = sinf(latAngle) * sinf(longAngle + longStep);
            float z3 = sinf(latAngle + latStep) * sinf(longAngle);
            float z4 = sinf(latAngle + latStep) * sinf(longAngle + longStep);
            float u1 = 1.0f - (float) j / longBands;
            float u2 = 1.0f - (float) (j + 1) / longBands;
            float v1 = 1.0f - (float) i / latBands;
            float v2 = 1.0f - (float) (i + 1) / latBands;
            int32_t vi = k * 3;
            int32_t ti = k * 2;

            mesh->positions[vi] = x1;
            mesh->positions[vi+1] = y1;
            mesh->positions[vi+2] = z1; //v0

            mesh->positions[vi+3] = x2;
            mesh->positions[vi+4] = y1;
            mesh->positions[vi+5] = z2; //v1

            mesh->positions[vi+6] = x3;
            mesh->positions[vi+7] = y2;
            mesh->positions[vi+8] = z3; // v2


            mesh->positions[vi+9] = x4;
            mesh->positions[vi+10] = y2;
            mesh->positions[vi+11] = z4; // v3

            mesh->normals[vi] = x1;
            mesh->normals[vi+1] = y1;
            mesh->normals[vi+2] = z1;

            mesh->normals[vi+3] = x2;
            mesh->normals[vi+4] = y1;
            mesh->normals[vi+5] = z2;

            mesh->normals[vi+6] = x3;
            mesh->normals[vi+7] = y2;
            mesh->normals[vi+8] = z3;

            mesh->normals[vi+9] = x4;
            mesh->normals[vi+10] = y2;
            mesh->normals[vi+11] = z4;

            mesh->uvs[ti] = u1;
            mesh->uvs[ti+1] = v1;

            mesh->uvs[ti+2] = u2;
            mesh->uvs[ti+3] = v1;

            mesh->uvs[ti+4] = u1;
            mesh->uvs[ti+5] = v2;

            mesh->uvs[ti+6] = u2;
            mesh->uvs[ti+7] = v2;

            mesh->indices[l    ] = k;
            mesh->indices[l + 1] = k + 1;
            mesh->indices[l + 2] = k + 2;
            mesh->indices[l + 3] = k + 2;
            mesh->indices[l + 4] = k + 1;
            mesh->indices[l + 5] = k + 3;

            k += 4;
            l += 6;
        }
    }
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
