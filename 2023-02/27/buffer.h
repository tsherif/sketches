#ifndef BUFFER_H_
#define BUFFER_H_

#include "../../lib/simple-opengl-loader.h"
#include <stdint.h>

typedef struct {
    GLuint handle;
} Buffer;

Buffer Buffer_create(void);
void Buffer_data(Buffer* buffer, void* data, uint32_t size);
void Buffer_bind(Buffer* buffer);

#endif