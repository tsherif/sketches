#include "object.h"

Object::Object(VertexArray& v, Program& p, uint32_t n) : vertexArray(v), program(p), numVerts(n){}

void Object::draw() {
    glBindVertexArray(vertexArray.handle);
    glUseProgram(program.handle);
    glDrawArrays(GL_TRIANGLES, 0, numVerts);
}