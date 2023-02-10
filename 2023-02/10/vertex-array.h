#ifndef VERTEX_ARRAY_H_
#define VERTEX_ARRAY_H_

#include <stdint.h>
#include <stdbool.h>
#include "buffer.h"

typedef struct {
    GLuint handle;
} VertexArray;

VertexArray VertexArray_create(void);
void VertexArray_vertexBuffer(VertexArray* vertexArray, GLuint index, Buffer* buffer, GLuint type, uint32_t vecSize, bool normalized);
void VertexArray_bind(VertexArray* vertexArray);

#endif