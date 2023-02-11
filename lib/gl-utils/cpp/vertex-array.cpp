#include "vertex-array.h"

VertexArray& VertexArray::init() {
    glGenVertexArrays(1, &handle);

     return *this;
}

VertexArray& VertexArray::vertexBuffer(GLuint index, Buffer& buffer, GLuint type, uint32_t vecSize, bool normalized) {
    bind();
    buffer.bind();
    glVertexAttribPointer(index, vecSize, type, normalized, 0, NULL);
    glEnableVertexAttribArray(index);
    unbind();

    return *this;
}

VertexArray& VertexArray::indexBuffer(Buffer& buffer) {
    bind();
    buffer.bind();
    unbind();
    
    return *this;
}

VertexArray& VertexArray::bind() {
    glBindVertexArray(handle);

    return *this;
}

VertexArray& VertexArray::unbind() {
    glBindVertexArray(0);

    return *this;
}