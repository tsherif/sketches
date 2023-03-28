#ifndef DATABASE_H_
#define DATABASE_H_

#include <stddef.h>

#include "buffer.h"
#include "vertex-array.h"
#include "program.h"

#define CONTAINER Database_BufferList
#define TYPE Buffer
#include "vector.h"

#define CONTAINER Database_VertexArrayList
#define TYPE VertexArray
#include "vector.h"

#define CONTAINER Database_ProgramList
#define TYPE Program
#include "vector.h"

typedef struct Database {
    Database_BufferList buffers;
    Database_VertexArrayList vertexArrays;
    Database_ProgramList programs;
} Database;

Database Database_create(void);

size_t Database_addBuffer(Database* db, Buffer buffer);
size_t Database_addVertexArray(Database* db, VertexArray vertexArray);
size_t Database_addProgram(Database* db, Program program);

Buffer Database_getBuffer(Database* db, size_t handle);
VertexArray Database_getVertexArray(Database* db, size_t handle);
Program Database_getProgram(Database* db, size_t handle);

#endif