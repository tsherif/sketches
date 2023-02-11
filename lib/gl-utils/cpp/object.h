#ifndef OBJECT_H_
#define OBJECT_H_

#include <stdint.h>
#include "../../simple-opengl-loader.h"
#include "program.h"
#include "vertex-array.h"

class Object {
    VertexArray vertexArray;
    Program program;
    uint32_t numVerts;

    public:
    Object(VertexArray& v, Program& p, uint32_t n);

    void draw();
};

#endif