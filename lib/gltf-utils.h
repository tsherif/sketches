#ifndef GLTF_UTILS
#define GLTF_UTILS

// Note: Assumes cgltf is already included.
#include "utils.h"

typedef struct {
    int32_t indexOffset;
    int32_t elementCount; 
    int32_t indexByteLength;
    int32_t positionOffset; 
    int32_t positionByteLength;
    int32_t normalOffset; 
    int32_t normalByteLength; 
    int32_t uvOffset; 
    int32_t uvByteLength; 
    char* bufferFilename;
    char* imageFilename;
} GLTF;

void parseGLTF(cgltf_data* gltf, GLTF* parsed) {
    cgltf_primitive* primitive = gltf->meshes[0].primitives;
    cgltf_accessor* indices = primitive->indices;

    parsed->indexOffset = (int32_t) (indices->offset + indices->buffer_view->offset);
    parsed->elementCount = (int32_t) indices->count; 
    parsed->indexByteLength = (int32_t) (parsed->elementCount * sizeof(uint16_t));

    for (int32_t i = 0; i < primitive->attributes_count; ++i) {
        cgltf_attribute* attribute = primitive->attributes + i;

        if (strEquals(attribute->name, "POSITION", sizeof("POSITION"))) {
            parsed->positionOffset = (int32_t) (attribute->data->offset + attribute->data->buffer_view->offset); 
            parsed->positionByteLength = (int32_t) (attribute->data->count * attribute->data->stride);
        } else if (strEquals(attribute->name, "NORMAL", sizeof("NORMAL"))) {
            parsed->normalOffset = (int32_t) (attribute->data->offset + attribute->data->buffer_view->offset); 
            parsed->normalByteLength = (int32_t) (attribute->data->count * attribute->data->stride);
        } else if (strEquals(attribute->name, "TEXCOORD_0", sizeof("TEXCOORD_0"))) {
            parsed->uvOffset = (int32_t) (attribute->data->offset + attribute->data->buffer_view->offset); 
            parsed->uvByteLength = (int32_t) (attribute->data->count * attribute->data->stride);
        }
    }

    parsed->bufferFilename = gltf->buffers[0].uri;
    parsed->imageFilename = gltf->images[0].uri;
}

#endif