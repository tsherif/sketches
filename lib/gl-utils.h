#ifndef GL_UTILS
#define GL_UTILS

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

#endif