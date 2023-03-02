#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "../../lib/c/simple-opengl-loader.h"

typedef struct {
    GLuint handle;
} Program;

typedef struct {
    const char* vsSource;
    const char* fsSource;
    void (*logFn)(const char*);
} Program_CreateOptions;

Program Program_create(Program_CreateOptions* options);
void Program_bind(Program* program);

#endif