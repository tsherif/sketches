#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <string>
#include <map>
#include "../../simple-opengl-loader.h"

class Program {
    public:
    GLuint handle = 0;
    Program& init(const char* vsSource, const char* fsSource, void logFn(const char*) = nullptr);
    Program& setFloatUniform(std::string name, float value);
    Program& setVec3Uniform(std::string name, const GLfloat* value);
    Program& setMat4Uniform(std::string name, const GLfloat* value);
    Program& setIntUniform(std::string name, GLint value);
    Program& bind();

    private:
    std::map<std::string, GLuint> uniformLocations;
    GLuint getLocation(std::string);
};

#endif