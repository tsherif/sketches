#include "object.h"

Object::Object(GLuint v, GLuint p, uint32_t n) : vao(v), program(p), numVerts(n){}

void Object::draw() {
    glBindVertexArray(vao);
    glUseProgram(program);
    glDrawArrays(GL_TRIANGLES, 0, numVerts);
}