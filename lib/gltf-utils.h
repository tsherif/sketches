#ifndef GLTF_UTILS
#define GLTF_UTILS

#include <malloc.h>

// Note: Assumes cgltf and HandmadeMath are already included.
#include "utils.h"
#include "gl-utils.h"

typedef struct {
    int32_t colorTexture;
    int32_t normalTexture;

    // G = Roughness, B = Metallness
    // https://registry.khronos.org/glTF/specs/2.0/glTF-2.0.html#metallic-roughness-material
    int32_t metallicRoughnessTexture;
} GLTF_Material;

typedef struct {
    Buffer buffer;
    GLTF_Material material; 
    float* positions; 
    float* normals; 
    float* tangents;
    float* uvs; 
    uint16_t* indices;
    int32_t vec3ArrayByteLength;
    int32_t vec2ArrayByteLength; 
    int32_t indicesByteLength;
    int32_t vertexCount;
    int32_t elementCount;
} GLTF_Mesh;

void parseGLTF(cgltf_mesh* mesh, cgltf_image* imageBase, Buffer* buffer, GLTF_Mesh* parsed) {
    cgltf_primitive* primitive = mesh->primitives;
    cgltf_accessor* indicesAccessor = primitive->indices;
    cgltf_material* material = primitive->material;

    parsed->buffer = *buffer;
    parsed->indices = (uint16_t *) (buffer->data + indicesAccessor->offset + indicesAccessor->buffer_view->offset);
    parsed->elementCount = (int32_t) indicesAccessor->count; 
    parsed->indicesByteLength = (int32_t) (parsed->elementCount * sizeof(uint16_t));
    parsed->material.colorTexture = (int32_t) (material->pbr_metallic_roughness.base_color_texture.texture->image - imageBase);
    parsed->material.normalTexture = (int32_t) (material->normal_texture.texture->image - imageBase);
    parsed->material.metallicRoughnessTexture = (int32_t) (material->pbr_metallic_roughness.metallic_roughness_texture.texture->image - imageBase);

    for (int32_t i = 0; i < primitive->attributes_count; ++i) {
        cgltf_attribute* attribute = primitive->attributes + i;
        parsed->vertexCount = (int32_t) attribute->data->count;

        float* attributeBuffer = (float *) (buffer->data + attribute->data->offset + attribute->data->buffer_view->offset);
        if (strEquals(attribute->name, "POSITION", sizeof("POSITION"))) {
            parsed->positions = attributeBuffer;
        } else if (strEquals(attribute->name, "NORMAL", sizeof("NORMAL"))) {
            parsed->normals = attributeBuffer; 
        } else if (strEquals(attribute->name, "TEXCOORD_0", sizeof("TEXCOORD_0"))) {
            parsed->uvs = attributeBuffer; 
        }
    }

    parsed->vec3ArrayByteLength = parsed->vertexCount * 3 * sizeof(float);
    parsed->vec2ArrayByteLength = parsed->vertexCount * 2 * sizeof(float);

    float* positions = parsed->positions;
    float* normals = parsed->normals;
    float* uvs = parsed->uvs;
    uint16_t* indices = parsed->indices;
    int32_t elementCount = parsed->elementCount;
    int32_t vertexCount = parsed->vertexCount;

    parsed->tangents = (float *) malloc(vertexCount * 3 * sizeof(float));
    generateTangents(
        parsed->positions,
        parsed->normals,
        parsed->uvs,
        parsed->indices,
        parsed->elementCount,
        parsed->vertexCount,
        parsed->tangents
    );
}

#endif