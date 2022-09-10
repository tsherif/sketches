#ifndef GLTF_UTILS
#define GLTF_UTILS

#include <malloc.h>

// Note: Assumes cgltf and HandmadeMath are already included.
#include "utils.h"

typedef struct {
    int32_t colorTexture;
    int32_t normalTexture;
} GLTF_Material;

typedef struct {
    Buffer buffer;
    GLTF_Material material; 
    uint8_t* positions; 
    uint8_t* normals; 
    uint8_t* tangents;
    uint8_t* uvs; 
    uint8_t* indices;
    int32_t positionsByteLength;
    int32_t normalsByteLength; 
    int32_t tangentsByteLength; 
    int32_t uvsByteLength;
    int32_t indicesByteLength;
    int32_t elementCount;
} GLTF_Mesh;

void parseGLTF(cgltf_mesh* mesh, cgltf_image* imageBase, Buffer* buffer, GLTF_Mesh* parsed) {
    cgltf_primitive* primitive = mesh->primitives;
    cgltf_accessor* indicesAccessor = primitive->indices;
    cgltf_material* material = primitive->material;

    parsed->buffer = *buffer;
    parsed->indices = buffer->data + indicesAccessor->offset + indicesAccessor->buffer_view->offset;
    parsed->elementCount = (int32_t) indicesAccessor->count; 
    parsed->indicesByteLength = (int32_t) (parsed->elementCount * sizeof(uint16_t));
    parsed->material.colorTexture = (int32_t) (material->pbr_metallic_roughness.base_color_texture.texture->image - imageBase);
    parsed->material.normalTexture = (int32_t) (material->normal_texture.texture->image - imageBase);

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

    // hmm_vec3 pos0 = HMM_Vec3(-1.0f, -1.0f, 0.0f);
    // hmm_vec3 pos1 = HMM_Vec3(1.0f, -1.0f, 0.0f);
    // hmm_vec3 pos2 = HMM_Vec3(1.0f, 1.0f, 0.0f);

    // hmm_vec2 uv0 = HMM_Vec2(0.0f, 0.0f);
    // hmm_vec2 uv1 = HMM_Vec2(1.0f, 0.0f);
    // hmm_vec2 uv2 = HMM_Vec2(1.0f, 1.0f);

    // hmm_vec3 edge0 = HMM_SubtractVec3(pos1, pos0);
    // hmm_vec3 edge1 = HMM_SubtractVec3(pos2, pos0);
    // hmm_vec2 duv0 = HMM_SubtractVec2(uv1, uv0);
    // hmm_vec2 duv1 = HMM_SubtractVec2(uv2, uv0);

    // float f = 1.0f / (duv0.X * duv1.Y - duv1.X * duv0.Y);

    // float tangentx = f * (duv1.Y * edge0.X - duv0.Y * edge1.X);
    // float tangenty = f * (duv1.Y * edge0.Y - duv0.Y * edge1.Y);
    // float tangentz = f * (duv1.Y * edge0.Z - duv0.Y * edge1.Z);

    float* positions = (float *) parsed->positions;
    float* uvs = (float *) parsed->uvs;
    uint16_t* indices = (uint16_t *) parsed->indices;
    int32_t count = parsed->elementCount;

    float* tangents = (float *) malloc(parsed->normalsByteLength);
    
    for (int32_t i = 0; i < count; i += 3) {
        int32_t i0 = indices[i];
        int32_t i1 = indices[i + 1];
        int32_t i2 = indices[i + 2];

        int32_t pi0 = i0 * 3;
        int32_t pi1 = i1 * 3;
        int32_t pi2 = i2 * 3;

        int32_t ui0 = i0 * 2;
        int32_t ui1 = i1 * 2;
        int32_t ui2 = i2 * 2;

        hmm_vec3 pos0 = HMM_Vec3(positions[pi0], positions[pi0 + 1], positions[pi0 + 2]);
        hmm_vec3 pos1 = HMM_Vec3(positions[pi1], positions[pi1 + 1], positions[pi1 + 2]);
        hmm_vec3 pos2 = HMM_Vec3(positions[pi2], positions[pi2 + 1], positions[pi2 + 2]);

        hmm_vec2 uv0 = HMM_Vec2(uvs[ui0], uvs[ui0 + 1]);
        hmm_vec2 uv1 = HMM_Vec2(uvs[ui1], uvs[ui1 + 1]);
        hmm_vec2 uv2 = HMM_Vec2(uvs[ui2], uvs[ui2 + 1]);

        hmm_vec3 edge0 = HMM_SubtractVec3(pos1, pos0);
        hmm_vec3 edge1 = HMM_SubtractVec3(pos2, pos0);
        hmm_vec2 duv0 = HMM_SubtractVec2(uv1, uv0);
        hmm_vec2 duv1 = HMM_SubtractVec2(uv2, uv0);

        float f = 1.0f / (duv0.X * duv1.Y - duv1.X * duv0.Y);

        hmm_vec3 tangent = HMM_NormalizeVec3(
            HMM_MultiplyVec3f(
                HMM_SubtractVec3(
                    HMM_MultiplyVec3f(edge0, duv1.Y),
                    HMM_MultiplyVec3f(edge1, duv0.Y)
                ),
                f
            );
        )

        tangents[pi0]     = tangent.X;
        tangents[pi0 + 1] = tangent.Y;
        tangents[pi0 + 2] = tangent.Z;

        tangents[pi1]     = tangent.X;
        tangents[pi1 + 1] = tangent.Y;
        tangents[pi1 + 2] = tangent.Z;

        tangents[pi2]     = tangent.X;
        tangents[pi2 + 1] = tangent.Y;
        tangents[pi2 + 2] = tangent.Z;
    }

    parsed->tangents = (uint8_t *) tangents;
    parsed->tangentsByteLength = parsed->normalsByteLength;
}

#endif