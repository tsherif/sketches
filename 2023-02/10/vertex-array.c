#include "vertex-array.h"

VertexArray VertexArray_create(void) {
    VertexArray vertexArray = { 0 };
    glGenVertexArrays(1, &vertexArray.handle);

    return vertexArray;
}

void VertexArray_vertexBuffer(VertexArray* vertexArray, GLuint index, Buffer* buffer, GLuint type, uint32_t vecSize, bool normalized) {
    VertexArray_bind(vertexArray);
    Buffer_bind(buffer);
    glVertexAttribPointer(index, vecSize, type, normalized, 0, NULL);
    glEnableVertexAttribArray(index);
}

void VertexArray_bind(VertexArray* vertexArray) {
    glBindVertexArray(vertexArray->handle);
}