#ifndef VERTEX_ARRAY_H_
#define VERTEX_ARRAY_H_

#include <stdint.h>
#include <stdbool.h>
#include "buffer.h"

typedef struct {
    GLuint handle;
} VertexArray;

typedef struct {
    GLuint index;
    Buffer* buffer;
    GLuint type;
    uint32_t vecSize;
    bool normalized;
} VertexArray_VertexBufferOptions;

VertexArray VertexArray_create(void);
void VertexArray_vertexBuffer(VertexArray* vertexArray, VertexArray_VertexBufferOptions* options);
void VertexArray_bind(VertexArray* vertexArray);

#endif