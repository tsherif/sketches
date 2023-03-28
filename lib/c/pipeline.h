#ifndef PIPELINE_H_
#define PIPELINE_H_

#include <stddef.h>
#include "../../lib/c/simple-opengl-loader.h"
typedef struct Database Database;

typedef struct {
    Database* db;
    size_t vertexArray;
    size_t program;
    GLuint primitive;
} Pipeline;

Pipeline Pipeline_create(Database* db, GLuint prim, size_t v, size_t p);
void Pipeline_draw(Pipeline* pipeline);

#endif