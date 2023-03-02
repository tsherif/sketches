#include "program.h"
#include "../../lib/c/gl-utils.h"

Program Program_create(Program_CreateOptions* options) {
    return (Program) {
        .handle = createProgram(
            options->vsSource,
            options->fsSource,
            options->logFn
        )
    };
}

void Program_bind(Program* program) {
    glUseProgram(program->handle);
}