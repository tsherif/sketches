#include "pipeline.h"
#include "database.h"
#include "vertex-array.h"
#include "program.h"

Pipeline Pipeline_create(GLuint prim, size_t v, size_t p, Database* db) {
    return (Pipeline) {
        .db = db,
        .vertexArray = v,
        .program = p,
        .primitive = prim
    };
}

void Pipeline_draw(Pipeline* pipeline) {
    VertexArray vertexArrayObj = Database_getVertexArray(pipeline->db, pipeline->vertexArray);
    Program programObj = Database_getProgram(pipeline->db, pipeline->program);

    glBindVertexArray(vertexArrayObj.handle);
    glUseProgram(programObj.handle);
    if (vertexArrayObj.indexed) {
        glDrawElements(pipeline->primitive, vertexArrayObj.numElements, vertexArrayObj.indexType, 0);
    } else {
        glDrawArrays(pipeline->primitive, 0, vertexArrayObj.numElements);
    }
}