#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "../../lib/gl-utils.h"

class Program {
    GLuint handle;

    public:

    Program(const char* vsSource, const char* fsSource, void logFn(const char*) = nullptr);

    GLuint getHandle();
};

#endif