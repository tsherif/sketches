#ifndef BUFFER_H_
#define BUFFER_H_

#include "../../lib/simple-opengl-loader.h"
#include <stddef.h>
#include <stdint.h>

typedef struct {
    GLuint handle;
    GLuint binding;
    GLsizei size;
} Buffer;

Buffer Buffer_create(GLuint binding);
void Buffer_data(Buffer* buffer, void* data, GLsizei size);
void Buffer_bind(Buffer* buffer);

#endif