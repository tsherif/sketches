#ifndef VERTEX_ARRAY_H_
#define VERTEX_ARRAY_H_

#include <stdint.h>
#include <stdbool.h>
#include "buffer.h"

typedef struct {
    GLuint handle;
    GLsizei numElements;
    GLuint indexType;
    bool indexed;
} VertexArray;

typedef struct {
    GLuint index;
    Buffer* buffer;
    GLuint type;
    GLsizei vecSize;
    bool normalized;
} VertexArray_VertexBufferOptions;

VertexArray VertexArray_create(void);
void VertexArray_vertexBuffer(VertexArray* vertexArray, VertexArray_VertexBufferOptions* options);
void VertexArray_indexBuffer(VertexArray* vertexArray, Buffer* buffer, GLuint type);
void VertexArray_bind(VertexArray* vertexArray);
void VertexArray_unbind(void);

#endif