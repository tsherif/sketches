#ifndef BUFFER_H_
#define BUFFER_H_

#include "../../simple-opengl-loader.h"
#include <stdint.h>

class Buffer {
    public: 
    GLuint handle;
    Buffer();
    Buffer& data(void* data, uint32_t size);
    Buffer& bind();
};

#endif