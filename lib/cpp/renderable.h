#ifndef OBJECT_H_
#define OBJECT_H_

#include <stdint.h>
#include "../../simple-opengl-loader.h"
#include "program.h"
#include "vertex-array.h"

class Renderable {
    VertexArray vertexArray;
    Program program;
    std::map<std::string, float> floatUniforms;
    std::map<std::string, const GLfloat*> vec3Uniforms;
    std::map<std::string, const GLfloat*> mat4Uniforms;
    std::map<std::string, int> intUniforms;

    public:
    Renderable& init(const VertexArray& v, const Program& p);
    Renderable& setFloatUniform(std::string name, float value);
    Renderable& setVec3Uniform(std::string name, const GLfloat* value);
    Renderable& setMat4Uniform(std::string name, const GLfloat* value);
    Renderable& setIntUniform(std::string name, GLint value);

    Renderable&  draw();
};

#endif