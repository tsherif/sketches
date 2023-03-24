#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "../../lib/c/simple-opengl-loader.h"

typedef struct {
    GLint size;
    GLenum type;
    GLint location;
} Program_UniformData;

#define CONTAINER Program_UniformMap
#define TYPE Program_UniformData
#include "../../lib/c/str-map.h"

typedef struct {
    GLuint handle;
    Program_UniformMap uniformData;
} Program;

typedef struct {
    const char* vsSource;
    const char* fsSource;
    void (*logFn)(const char*);
} Program_CreateOptions;

Program Program_create(Program_CreateOptions* options);
void Program_setVecUniform(Program* program, const char* name, const void* value);
void Program_setIntUniform(Program* program, const char* name, GLint value);
void Program_bind(Program* program);

#endif