#include "program.h"
#include "../../lib/c/gl-utils.h"

Program::Program(const char* vsSource, const char* fsSource, void logFn(const char*)) {
    handle = createProgram(
        vsSource,
        fsSource,
        logFn
    );
}

GLuint Program::getHandle() {
    return handle;
}