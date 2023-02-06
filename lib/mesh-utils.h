#ifndef MESH_UTILS_H
#define MESH_UTILS_H
#include <string.h>

void generateTangents(float* positions, float* normals, float* uvs, uint16_t* indices, int32_t elementCount, int32_t vertexCount, float* tangents) {
    memset(tangents, 0, vertexCount * 3 * sizeof(float));

    for (int32_t i = 0; i < elementCount; i += 3) {
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
            )
        );

        tangents[pi0]     += tangent.X;
        tangents[pi0 + 1] += tangent.Y;
        tangents[pi0 + 2] += tangent.Z;

        tangents[pi1]     += tangent.X;
        tangents[pi1 + 1] += tangent.Y;
        tangents[pi1 + 2] += tangent.Z;

        tangents[pi2]     += tangent.X;
        tangents[pi2 + 1] += tangent.Y;
        tangents[pi2 + 2] += tangent.Z;
    }

    // Average and orthogonalize tangents.
    for (int32_t i = 0; i < vertexCount; ++i) {
        int32_t ti = i * 3;

        hmm_vec3 n = HMM_Vec3(normals[ti], normals[ti + 1], normals[ti + 2]);
        hmm_vec3 t = HMM_NormalizeVec3(HMM_Vec3(tangents[ti], tangents[ti + 1], tangents[ti + 2]));

        hmm_vec3 orthogonalTangent = HMM_NormalizeVec3(
            HMM_SubtractVec3(
                t, 
                HMM_MultiplyVec3f(
                    n, 
                    HMM_DotVec3(n, t)
                )
            )
        );

        tangents[ti]     = orthogonalTangent.X;
        tangents[ti + 1] = orthogonalTangent.Y;
        tangents[ti + 2] = orthogonalTangent.Z;
    }
}

#endif