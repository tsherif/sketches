#ifndef BUFFER_H_
#define BUFFER_H_

#include "../../simple-opengl-loader.h"
#include <stdint.h>

class Buffer {
    private:
    GLuint binding = 0;
    
    public: 
    GLuint handle = 0;
    Buffer& init(GLuint binding = GL_ARRAY_BUFFER);
    Buffer& data(void* data, uint32_t size);
    Buffer& bind();
};

#endif