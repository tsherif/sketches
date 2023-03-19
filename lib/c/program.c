#include "program.h"
#include "../../lib/c/gl-utils.h"

#define CONTAINER Program_UniformMap
#define TYPE GLint
#define IMPLEMENTATION_ONLY
#include "../../lib/c/str-map.h"

static GLint getLocation(Program* program, const char* name) {
    if (!Program_UniformMap_has(&program->uniformLocations, name)) {
        Program_UniformMap_set(&program->uniformLocations, name, glGetUniformLocation(program->handle, name));
    }

    return Program_UniformMap_get(&program->uniformLocations, name);
}

Program Program_create(Program_CreateOptions* options) {
    return (Program) {
        .handle = createProgram(
            options->vsSource,
            options->fsSource,
            options->logFn
        ),
        .uniformLocations = Program_UniformMap_create()
    };
}

void Program_setVec3Uniform(Program* program, const char* name, const GLfloat* value) {
    Program_bind(program);
    GLint location = getLocation(program, name);
    glUniform3fv(location, 1, value);

}

void Program_setMat4Uniform(Program* program, const char* name, const GLfloat* value) {
    Program_bind(program);
    GLint location = getLocation(program, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, value);
}

void Program_setIntUniform(Program* program, const char* name, GLint value) {
    Program_bind(program);
    GLint location = getLocation(program, name);
    glUniform1i(location, value);
}


void Program_bind(Program* program) {
    glUseProgram(program->handle);
}