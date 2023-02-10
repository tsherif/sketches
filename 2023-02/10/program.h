#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "../../lib/simple-opengl-loader.h"

typedef struct {
    GLuint handle;
} Program;

Program Program_create(const char* vsSource, const char* fsSource, void logFn(const char*));
void Program_bind(Program* program);

#endif