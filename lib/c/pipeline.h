#ifndef PIPELINE_H_
#define PIPELINE_H_

#include <stdint.h>
#include "../../lib/c/simple-opengl-loader.h"
#include "program.h"
#include "vertex-array.h"

typedef struct {
    VertexArray* vertexArray;
    Program* program;
    GLuint primitive;
} Pipeline;

Pipeline Pipeline_create(GLuint prim, VertexArray* v, Program* p);
void Pipeline_draw(Pipeline* pipeline);

#endif