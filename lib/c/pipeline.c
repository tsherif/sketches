#include "pipeline.h"

Pipeline Pipeline_create(GLuint prim, VertexArray* v, Program* p)  {
    return (Pipeline) {
        .vertexArray = v,
        .program = p,
        .primitive = prim
    };
}

void Pipeline_draw(Pipeline* pipeline) {
    glBindVertexArray(pipeline->vertexArray->handle);
    glUseProgram(pipeline->program->handle);
    if (pipeline->vertexArray->indexed) {
        glDrawElements(pipeline->primitive, pipeline->vertexArray->numElements, pipeline->vertexArray->indexType, 0);
    } else {
        glDrawArrays(pipeline->primitive, 0, pipeline->vertexArray->numElements);
    }
}