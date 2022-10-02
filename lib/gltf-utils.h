#ifndef GLTF_UTILS
#define GLTF_UTILS

#include <malloc.h>

// Note: Assumes cgltf and HandmadeMath are already included.
#include "utils.h"

typedef struct {
    int32_t colorTexture;
    int32_t normalTexture;

    // R = Metallness, G = Roughness
    // https://github.com/sbtron/glTF/blob/30de0b365d1566b1bbd8b9c140f9e995d3203226/specification/2.0/README.md#pbrmetallicroughnessmetallicroughnesstexture
    int32_t metallicRoughnessTexture;
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
    parsed->material.metallicRoughnessTexture = (int32_t) (material->pbr_metallic_roughness.metallic_roughness_texture.texture->image - imageBase);

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

    float* positions = (float *) parsed->positions;
    float* normals = (float *) parsed->normals;
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

        hmm_vec3 n0 = HMM_Vec3(normals[pi0], normals[pi0 + 1], normals[pi0 + 2]);
        hmm_vec3 n1 = HMM_Vec3(normals[pi1], normals[pi1 + 1], normals[pi1 + 2]);
        hmm_vec3 n2 = HMM_Vec3(normals[pi2], normals[pi2 + 1], normals[pi2 + 2]);

        hmm_vec2 uv0 = HMM_Vec2(uvs[ui0], uvs[ui0 + 1]);
        hmm_vec2 uv1 = HMM_Vec2(uvs[ui1], uvs[ui1 + 1]);
        hmm_vec2 uv2 = HMM_Vec2(uvs[ui2], uvs[ui2 + 1]);

        hmm_vec3 edge0 = HMM_SubtractVec3(pos1, pos0);
        hmm_vec3 edge1 = HMM_SubtractVec3(pos2, pos0);
        hmm_vec2 duv0 = HMM_SubtractVec2(uv1, uv0);
        hmm_vec2 duv1 = HMM_SubtractVec2(uv2, uv0);

        float f = 1.0f / (duv0.X * duv1.Y - duv1.X * duv0.Y);

        hmm_vec3 tangent = HMM_MultiplyVec3f(
            HMM_SubtractVec3(
                HMM_MultiplyVec3f(edge0, duv1.Y),
                HMM_MultiplyVec3f(edge1, duv0.Y)
            ),
            f
        );

        hmm_vec3 tangent0 = HMM_NormalizeVec3(
            HMM_SubtractVec3(
                tangent, 
                HMM_MultiplyVec3f(
                    n0, 
                    HMM_DotVec3(n0, tangent)
                )
            )
        );

        hmm_vec3 tangent1 = HMM_NormalizeVec3(
            HMM_SubtractVec3(
                tangent, 
                HMM_MultiplyVec3f(
                    n1, 
                    HMM_DotVec3(n1, tangent)
                )
            )
        );

        hmm_vec3 tangent2 = HMM_NormalizeVec3(
            HMM_SubtractVec3(
                tangent, 
                HMM_MultiplyVec3f(
                    n2, 
                    HMM_DotVec3(n2, tangent)
                )
            )
        );

        // TODO(Tarek): This is incorrect. I'm only taking the last calculated tangent.
        // I should be averaging them.

        tangents[pi0]     = tangent0.X;
        tangents[pi0 + 1] = tangent0.Y;
        tangents[pi0 + 2] = tangent0.Z;

        tangents[pi1]     = tangent1.X;
        tangents[pi1 + 1] = tangent1.Y;
        tangents[pi1 + 2] = tangent1.Z;

        tangents[pi2]     = tangent2.X;
        tangents[pi2 + 1] = tangent2.Y;
        tangents[pi2 + 2] = tangent2.Z;
    }

    parsed->tangents = (uint8_t *) tangents;
    parsed->tangentsByteLength = parsed->normalsByteLength;
}

#endif