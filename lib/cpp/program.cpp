#include "program.h"
#include "../lib/c/utils.h"

Program& Program::init(const char* vsSource, const char* fsSource, void logFn(const char*)) {
    handle = createProgram(
        vsSource,
        fsSource,
        logFn
    );

    return *this;
}

Program& Program::setFloatUniform(std::string name, GLfloat value) {
    bind();
    GLuint location = getLocation(name);

    glUniform1f(location, value);

    return *this;
}

Program& Program::setVec3Uniform(std::string name, const GLfloat* value) {
    bind();
    GLuint location = getLocation(name);

    glUniform3fv(location, 1, value);

    return *this;
}

Program& Program::setMat4Uniform(std::string name, const GLfloat* value) {
    bind();
    GLuint location = getLocation(name);

    glUniformMatrix4fv(location, 1, GL_FALSE, value);

    return *this;
}

Program& Program::setIntUniform(std::string name, GLint value) {
    bind();
    GLuint location = getLocation(name);

    glUniform1i(location, value);

    return *this;
}

Program& Program::bind() {
    glUseProgram(handle);

    return *this;
}


GLuint Program::getLocation(std::string name) {
    if (uniformLocations.count(name) == 0) {
        uniformLocations[name] = glGetUniformLocation(handle, name.c_str());
    }

    return uniformLocations[name];
}