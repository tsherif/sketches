#include "vertex-array.h"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &handle);
}

VertexArray& VertexArray::vertexBuffer(GLuint index, Buffer& buffer, GLuint type, uint32_t vecSize, bool normalized) {
    bind();
    buffer.bind();
    glVertexAttribPointer(index, vecSize, type, normalized, 0, NULL);
    glEnableVertexAttribArray(index);

    return *this;
}

VertexArray& VertexArray::bind() {
    glBindVertexArray(handle);

    return *this;
}