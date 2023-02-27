#include "vertex-array.h"

VertexArray VertexArray_create(void) {
    VertexArray vertexArray = { 0 };
    glGenVertexArrays(1, &vertexArray.handle);

    return vertexArray;
}

void VertexArray_vertexBuffer(VertexArray* vertexArray, VertexArray_VertexBufferOptions* options) {
    VertexArray_bind(vertexArray);
    Buffer_bind(options->buffer);
    glVertexAttribPointer(options->index, options->vecSize, options->type, options->normalized, 0, NULL);
    glEnableVertexAttribArray(options->index);
}

void VertexArray_bind(VertexArray* vertexArray) {
    glBindVertexArray(vertexArray->handle);
}