#ifndef VERTEX_ARRAY_H_
#define VERTEX_ARRAY_H_

#include <stdint.h>
#include "buffer.h"

class VertexArray{
    public:
    GLuint handle = 0;
    VertexArray& init();
    VertexArray& vertexBuffer(GLuint index, Buffer& buffer, GLuint type, uint32_t vecSize, bool normalized = false);
    VertexArray& indexBuffer(Buffer& buffer);
    VertexArray& bind();
};

#endif