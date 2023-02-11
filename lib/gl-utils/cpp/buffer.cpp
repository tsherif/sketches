#include "buffer.h"

Buffer::Buffer(GLuint b): binding(b) {
    if (glGenBuffers) {
        glGenBuffers(1, &handle);
    }
}

Buffer& Buffer::data(void* data, uint32_t size) {
    if (!handle) {
        return *this;
    }

    glBindVertexArray(0);
    glBindBuffer(binding, handle);
    glBufferData(binding, size, data, GL_STATIC_DRAW);
    glBindBuffer(binding, 0);

    return *this;
}

Buffer& Buffer::bind() {
    if (!handle) {
        return *this;
    }

    glBindBuffer(binding, handle);

    return *this;
}