#ifndef PIPELINE_H_
#define PIPELINE_H_

#include <stddef.h>
#include "../../lib/c/simple-opengl-loader.h"
#include "database.h"

typedef struct {
    Database* db;
    size_t vertexArray;
    size_t program;
    GLuint primitive;
} Pipeline;

Pipeline Pipeline_create(GLuint prim, size_t v, size_t p, Database* db);
void Pipeline_draw(Pipeline* pipeline);

#endif