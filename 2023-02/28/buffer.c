#include "buffer.h"

Buffer Buffer_create(GLuint binding) {
    Buffer buffer = { 
        .binding = binding
    };
    glGenBuffers(1, &buffer.handle);

    return buffer;
}

void Buffer_data(Buffer* buffer, void* data, GLsizei size) {
    glBindBuffer(buffer->binding, buffer->handle);
    glBufferData(buffer->binding, size, data, GL_STATIC_DRAW);
    buffer->size = size;
}

void Buffer_bind(Buffer* buffer) {
    glBindBuffer(buffer->binding, buffer->handle);
}