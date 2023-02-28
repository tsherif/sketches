#include "vertex-array.h"

uint32_t getElementSize(GLuint type) {
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

VertexArray& VertexArray::init() {
    glGenVertexArrays(1, &handle);

    return *this;
}

VertexArray& VertexArray::vertexBuffer(GLuint index, Buffer& buffer, GLuint type, uint32_t vecSize, bool normalized) {
    if (!handle) {
        return *this;
    }

    bind();
    buffer.bind();
    glVertexAttribPointer(index, vecSize, type, normalized, 0, NULL);
    glEnableVertexAttribArray(index);
    unbind();


    if (!indexed) {
        numElements = buffer.size / (vecSize * getElementSize(type));
    }

    return *this;
}

VertexArray& VertexArray::indexBuffer(Buffer& buffer, GLuint type) {
    if (!handle) {
        return *this;
    }

    bind();
    buffer.bind();
    unbind();

    numElements = buffer.size / getElementSize(type);
    indexType = type;
    indexed = true;

    return *this;
}

VertexArray& VertexArray::bind() {
    if (!handle) {
        return *this;
    }

    glBindVertexArray(handle);

    return *this;
}

VertexArray& VertexArray::unbind() {
    if (!handle) {
        return *this;
    }

    glBindVertexArray(0);

    return *this;
}