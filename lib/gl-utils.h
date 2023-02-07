#ifndef GL_UTILS
#define GL_UTILS

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "simple-opengl-loader.h"

GLuint createProgram(const char* vsSource, const char* fsSource, void logFn(const char*));

typedef struct {
    GLuint vbo;
    GLuint attributeIndex;
    void* data;
    int32_t dataByteLength;
    GLenum type;
    GLint vectorSize;
    bool normalized;
} AttributeBufferDataOpts;

void attributeBufferData(AttributeBufferDataOpts* opts);

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

void textureData2D(TextureData2DOpts* opts);

#ifdef __cplusplus
}
#endif

#endif