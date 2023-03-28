#include "database.h"

#define CONTAINER Database_BufferList
#define TYPE Buffer
#define IMPLEMENTATION_ONLY
#include "vector.h"

#define CONTAINER Database_VertexArrayList
#define TYPE VertexArray
#define IMPLEMENTATION_ONLY
#include "vector.h"

#define CONTAINER Database_ProgramList
#define TYPE Program
#define IMPLEMENTATION_ONLY
#include "vector.h"

Database Database_create(void) {
    return (Database) {
        .buffers = Database_BufferList_create(),
        .vertexArrays = Database_VertexArrayList_create(),
        .programs = Database_ProgramList_create()
    };
}

size_t Database_addBuffer(Database* db, Buffer buffer) {
    size_t handle = Database_BufferList_size(&db->buffers);
    Database_BufferList_push(&db->buffers, buffer);
    return handle;
}

size_t Database_addVertexArray(Database* db, VertexArray vertexArray) {
    size_t handle = Database_VertexArrayList_size(&db->vertexArrays);
    Database_VertexArrayList_push(&db->vertexArrays, vertexArray);
    return handle;
}

size_t Database_addProgram(Database* db, Program program) {
    size_t handle = Database_ProgramList_size(&db->programs);
    Database_ProgramList_push(&db->programs, program);
    return handle;
}

Buffer Database_getBuffer(Database* db, size_t handle) {
    return Database_BufferList_get(&db->buffers, handle);
}

VertexArray Database_getVertexArray(Database* db, size_t handle) {
    return Database_VertexArrayList_get(&db->vertexArrays, handle);
}

Program Database_getProgram(Database* db, size_t handle) {
    return Database_ProgramList_get(&db->programs, handle);
}