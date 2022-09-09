#ifndef GLTF_UTILS
#define GLTF_UTILS

// Note: Assumes cgltf is already included.
#include "utils.h"

typedef struct {
    int32_t colorTexture;
} GLTF_Material;

typedef struct {
    Buffer buffer;
    GLTF_Material material; 
    uint8_t* positions; 
    uint8_t* normals; 
    uint8_t* uvs; 
    uint8_t* indices;
    int32_t positionsByteLength;
    int32_t normalsByteLength; 
    int32_t uvsByteLength;
    int32_t indicesByteLength;
    int32_t elementCount;
} GLTF_Mesh;

void parseGLTF(cgltf_mesh* mesh, cgltf_image* imageBase, Buffer* buffer, GLTF_Mesh* parsed) {
    cgltf_primitive* primitive = mesh->primitives;
    cgltf_accessor* indices = primitive->indices;
    cgltf_material* material = primitive->material;

    parsed->buffer = *buffer;
    parsed->indices = buffer->data + indices->offset + indices->buffer_view->offset;
    parsed->elementCount = (int32_t) indices->count; 
    parsed->indicesByteLength = (int32_t) (parsed->elementCount * sizeof(uint16_t));
    parsed->material.colorTexture = (int32_t) (material->pbr_metallic_roughness.base_color_texture.texture->image - imageBase);

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