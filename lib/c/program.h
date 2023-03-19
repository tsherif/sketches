#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "../../lib/c/simple-opengl-loader.h"

#define CONTAINER Program_UniformMap
#define TYPE GLint
#include "../../lib/c/str-map.h"

typedef struct {
    GLuint handle;
    Program_UniformMap uniformLocations;
} Program;

typedef struct {
    const char* vsSource;
    const char* fsSource;
    void (*logFn)(const char*);
} Program_CreateOptions;

Program Program_create(Program_CreateOptions* options);
void Program_setVec3Uniform(Program* program, const char* name, const GLfloat* value);
void Program_setMat4Uniform(Program* program, const char* name, const GLfloat* value);
void Program_setIntUniform(Program* program, const char* name, GLint value);
void Program_bind(Program* program);

#endif