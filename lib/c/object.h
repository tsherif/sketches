#ifndef OBJECT_H_
#define OBJECT_H_

#include <stdint.h>
#include "../../lib/c/simple-opengl-loader.h"
#include "program.h"
#include "vertex-array.h"

typedef struct {
    VertexArray* vertexArray;
    Program* program;
    uint32_t numVerts;
} Object;

Object Object_create(VertexArray* v, Program* p, uint32_t n);
void Object_draw(Object* object);

#endif