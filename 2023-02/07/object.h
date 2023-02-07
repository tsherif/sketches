#ifndef OBJECT_H_
#define OBJECT_H_

#include <stdint.h>
#include "../../lib/simple-opengl-loader.h"

class Object {
    GLuint vao;
    GLuint program;
    uint32_t numVerts;

    public:
    Object(GLuint v, GLuint p, uint32_t n);

    void draw();
};

#endif