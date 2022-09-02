#ifndef GL_UTILS
#define GL_UTILS

#include "../../lib/simple-opengl-loader.h"

GLuint createProgram(const char* vsSource, const char* fsSource, void (*logFn)(const char*)) {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vsSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fsSource, NULL);
    glCompileShader(fragmentShader);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint result;
    glGetProgramiv(program, GL_LINK_STATUS, &result);

    if (result != GL_TRUE) {
        if (logFn) {
            logFn("Program failed to link!\n");
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
            char errorLog[1024];
            if (result != GL_TRUE) {
                logFn("Vertex shader failed to compile!\n");
                glGetShaderInfoLog(vertexShader, 1024, NULL, errorLog);
                logFn(errorLog);
            }
            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
            if (result != GL_TRUE) {
                logFn("Fragment shader failed to compile!\n");
                glGetShaderInfoLog(fragmentShader, 1024, NULL, errorLog);
                logFn(errorLog);
            }
        }

        return 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

#endif