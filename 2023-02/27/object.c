#include "object.h"

Object Object_create(VertexArray* v, Program* p, uint32_t n)  {
    return (Object) {
        .vertexArray = v,
        .program = p,
        .numVerts = n
    };
}

void Object_draw(Object* object) {
    glBindVertexArray(object->vertexArray->handle);
    glUseProgram(object->program->handle);
    glDrawArrays(GL_TRIANGLES, 0, object->numVerts);
}