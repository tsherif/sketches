#ifndef GLTF_UTILS
#define GLTF_UTILS

// Note: Assumes cgltf is already included.
#include "utils.h"

typedef struct {
    Buffer buffer;
    uint8_t* positions; 
    uint8_t* normals; 
    uint8_t* uvs; 
    uint8_t* indices;
    int32_t positionsByteLength;
    int32_t normalsByteLength; 
    int32_t uvsByteLength;
    int32_t indicesByteLength;
    int32_t elementCount; 
} GLTF;

void parseGLTF(cgltf_data* gltf, Buffer* buffer, GLTF* parsed) {
    cgltf_primitive* primitive = gltf->meshes[0].primitives;
    cgltf_accessor* indices = primitive->indices;

    parsed->buffer = *buffer;
    parsed->indices = buffer->data + indices->offset + indices->buffer_view->offset;
    parsed->elementCount = (int32_t) indices->count; 
    parsed->indicesByteLength = (int32_t) (parsed->elementCount * sizeof(uint16_t));

    for (int32_t i = 0; i < primitive->attributes_count; ++i) {
        cgltf_attribute* attribute = primitive->attributes + i;

        if (strEquals(attribute->name, "POSITION", sizeof("POSITION"))) {
            parsed->positions = buffer->data + attribute->data->offset + attribute->data->buffer_view->offset; 
            parsed->positionsByteLength = (int32_t) (attribute->data->count * attribute->data->stride);
        } else if (strEquals(attribute->name, "NORMAL", sizeof("NORMAL"))) {
            parsed->normals = buffer->data + attribute->data->offset + attribute->data->buffer_view->offset; 
            parsed->normalsByteLength = (int32_t) (attribute->data->count * attribute->data->stride);
        } else if (strEquals(attribute->name, "TEXCOORD_0", sizeof("TEXCOORD_0"))) {
            parsed->uvs = buffer->data + attribute->data->offset + attribute->data->buffer_view->offset; 
            parsed->uvsByteLength = (int32_t) (attribute->data->count * attribute->data->stride);
        }
    }
}

#endif