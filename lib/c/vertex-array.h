#ifndef VERTEX_ARRAY_H_
#define VERTEX_ARRAY_H_

#include <stdint.h>
#include <stdbool.h>
#include "../../lib/c/simple-opengl-loader.h"
typedef struct Database Database;

typedef struct {
    Database* db;
    GLuint handle;
    GLsizei numElements;
    GLuint indexType;
    bool indexed;
} VertexArray;

typedef struct {
    GLuint index;
    size_t buffer;
    GLuint type;
    GLsizei vecSize;
    bool normalized;
} VertexArray_VertexBufferOptions;

VertexArray VertexArray_create(Database* db);
void VertexArray_vertexBuffer(VertexArray* vertexArray, VertexArray_VertexBufferOptions* options);
void VertexArray_indexBuffer(VertexArray* vertexArray, size_t buffer, GLuint type);
void VertexArray_bind(VertexArray* vertexArray);
void VertexArray_unbind(void);

#endif