#include "program.h"
#include "../../lib/c/gl-utils.h"

static GLint getLocation(Program* program, const char* name) {
    if (!StrMap_GLint_has(&program->uniformLocations, name)) {
        StrMap_GLint_set(&program->uniformLocations, name, glGetUniformLocation(program->handle, name));
    }

    return StrMap_GLint_get(&program->uniformLocations, name);
}

Program Program_create(Program_CreateOptions* options) {
    return (Program) {
        .handle = createProgram(
            options->vsSource,
            options->fsSource,
            options->logFn
        ),
        .uniformLocations = StrMap_GLint_create()
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