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
    mesh->positions = (float *) malloc(mesh->vertexCount * 3 * sizeof(float));
    mesh->normals = (float *) malloc(mesh->vertexCount * 3 * sizeof(float));
    mesh->uvs = (float *) malloc(mesh->vertexCount * 2 * sizeof(float));
    mesh->indices = (uint16_t *) malloc(mesh->elementCount * sizeof(uint16_t));
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

#endif