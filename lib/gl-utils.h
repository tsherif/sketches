#ifndef GL_UTILS
#define GL_UTILS

#include <string.h>
#include "../../lib/simple-opengl-loader.h"

GLuint createProgram(const char* vsSource, const char* fsSource, void (*logFn)(const char*)) {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vsSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fsSource, NULL);
    glCompileShader(fragmentShader);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint result;
    glGetProgramiv(program, GL_LINK_STATUS, &result);

    if (result != GL_TRUE) {
        if (logFn) {
            char errorLog[1024];
            logFn("Program failed to link!\n");
            glGetProgramInfoLog(program, 1024, NULL, errorLog);
            logFn(errorLog);

            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
            if (result != GL_TRUE) {
                logFn("Vertex shader failed to compile!\n");
                glGetShaderInfoLog(vertexShader, 1024, NULL, errorLog);
                logFn(errorLog);
            }
            
            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
            if (result != GL_TRUE) {
                logFn("Fragment shader failed to compile!\n");
                glGetShaderInfoLog(fragmentShader, 1024, NULL, errorLog);
                logFn(errorLog);
            }
        }

        return 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

typedef struct {
    GLuint vbo;
    GLuint attributeIndex;
    float* data;
    int32_t dataByteLength;
    GLenum type;
    GLint vectorSize;
} AttributeBufferDataOpts;

void attributeBufferData(AttributeBufferDataOpts* opts) {
    glBindBuffer(GL_ARRAY_BUFFER, opts->vbo);
    glBufferData(GL_ARRAY_BUFFER, opts->dataByteLength, opts->data, GL_STATIC_DRAW);
    glVertexAttribPointer(opts->attributeIndex, opts->vectorSize, opts->type, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(opts->attributeIndex);
}

typedef struct {
    GLuint texture;
    int32_t textureIndex;
    uint8_t* data;
    int32_t width;
    int32_t height;
    GLenum format;
    GLenum internalFormat;
    GLenum type;
} TextureData2DOpts;

void textureData2D(TextureData2DOpts* opts) {
    glActiveTexture(GL_TEXTURE0 + opts->textureIndex);
    glBindTexture(GL_TEXTURE_2D, opts->texture);
    glTexImage2D(GL_TEXTURE_2D, 0, opts->internalFormat, opts->width, opts->height, 0, opts->format, opts->type, opts->data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
}

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