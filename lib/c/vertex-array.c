#include "vertex-array.h"
#include "database.h"
#include "buffer.h"

static uint32_t getElementSize(GLuint type) {
    switch (type) {
        case GL_FLOAT:
        case GL_INT:
        case GL_UNSIGNED_INT:
            return 4;
        case GL_SHORT:
        case GL_UNSIGNED_SHORT:
            return 2;
        case GL_BYTE:
        case GL_UNSIGNED_BYTE:
            return 1;      
    }

    return 0;
}

VertexArray VertexArray_create(Database* db) {
    VertexArray vertexArray = { .db = db };
    glGenVertexArrays(1, &vertexArray.handle);

    return vertexArray;
}

void VertexArray_vertexBuffer(VertexArray* vertexArray, VertexArray_VertexBufferOptions* options) {
    Buffer bufferObject = Database_getBuffer(vertexArray->db, options->buffer);
    
    VertexArray_bind(vertexArray);
    Buffer_bind(&bufferObject);
    glVertexAttribPointer(options->index, options->vecSize, options->type, options->normalized, 0, NULL);
    glEnableVertexAttribArray(options->index);
    VertexArray_unbind();

    if (!vertexArray->indexed) {
        vertexArray->numElements = bufferObject.size / (options->vecSize * getElementSize(options->type));
    }
}

void VertexArray_indexBuffer(VertexArray* vertexArray, size_t buffer, GLuint type) {
    Buffer bufferObject = Database_getBuffer(vertexArray->db, buffer);


    VertexArray_bind(vertexArray);
    Buffer_bind(&bufferObject);
    VertexArray_unbind();

    vertexArray->numElements = bufferObject.size / getElementSize(type);
    vertexArray->indexType = type;
    vertexArray->indexed = true;
}

void VertexArray_bind(VertexArray* vertexArray) {
    glBindVertexArray(vertexArray->handle);
}

void VertexArray_unbind(void) {
    glBindVertexArray(0);
}