#include "object.h"

Object::Object(GLuint v, Program& p, uint32_t n) : vao(v), program(p), numVerts(n){}

void Object::draw() {
    glBindVertexArray(vao);
    glUseProgram(program.getHandle());
    glDrawArrays(GL_TRIANGLES, 0, numVerts);
}