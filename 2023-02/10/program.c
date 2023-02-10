#include "program.h"
#include "../../lib/gl-utils.h"

Program Program_create(const char* vsSource, const char* fsSource, void logFn(const char*));

Program Program_create(const char* vsSource, const char* fsSource, void logFn(const char*)) {
    return (Program) {
        .handle = createProgram(
            vsSource,
            fsSource,
            logFn
        )
    };
}

void Program_bind(Program* program) {
    glUseProgram(program->handle);
}