#ifndef VERTEX_ARRAY_H_
#define VERTEX_ARRAY_H_

#include <stdint.h>
#include "buffer.h"

class VertexArray{
    public:
    GLuint handle = 0;
    GLuint numElements = 0;
    GLuint indexType = 0;
    bool indexed = false;
    VertexArray& init();
    VertexArray& vertexBuffer(GLuint index, Buffer& buffer, GLuint type, uint32_t vecSize, bool normalized = false);
    VertexArray& indexBuffer(Buffer& buffer, GLuint type);
    VertexArray& bind();
    VertexArray& VertexArray::unbind();
};

#endif