#include "program.h"
#include "../lib/gl-utils.h"

Program& Program::init(const char* vsSource, const char* fsSource, void logFn(const char*)) {
    handle = createProgram(
        vsSource,
        fsSource,
        logFn
    );

    return *this;
}