#include "buffer.h"

Buffer Buffer_create(void) {
    Buffer buffer = { 0 };
    glGenBuffers(1, &buffer.handle);

    return buffer;
}

void Buffer_data(Buffer* buffer, void* data, uint32_t size) {
    glBindBuffer(GL_ARRAY_BUFFER, buffer->handle);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void Buffer_bind(Buffer* buffer) {
    glBindBuffer(GL_ARRAY_BUFFER, buffer->handle);
}