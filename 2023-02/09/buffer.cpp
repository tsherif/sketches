#include "buffer.h"

Buffer::Buffer() {
    glGenBuffers(1, &handle);
}

Buffer& Buffer::data(void* data, uint32_t size) {
    glBindBuffer(GL_ARRAY_BUFFER, handle);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    return *this;
}

Buffer& Buffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, handle);

    return *this;
}