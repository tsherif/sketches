#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "../../simple-opengl-loader.h"

class Program {
    public:
    GLuint handle = 0;
    Program() = default;
    Program(const char* vsSource, const char* fsSource, void logFn(const char*) = nullptr);
};

#endif