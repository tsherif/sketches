#ifndef OBJECT_H_
#define OBJECT_H_

#include <stdint.h>
#include "../../lib/simple-opengl-loader.h"
#include "program.h"

class Object {
    GLuint vao;
    Program program;
    uint32_t numVerts;

    public:
    Object(GLuint v, Program& p, uint32_t n);

    void draw();
};

#endif