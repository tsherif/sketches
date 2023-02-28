#include "renderable.h"

Renderable& Renderable::init(const VertexArray& v, const Program& p) {
    vertexArray = v;
    program = p;

    return *this;
}

Renderable& Renderable::setFloatUniform(std::string name, GLfloat value) {
    floatUniforms[name] = value;

    return *this;
}

Renderable& Renderable::setVec3Uniform(std::string name, const GLfloat* value) {
    vec3Uniforms[name] = value;

    return *this;
}

Renderable& Renderable::setMat4Uniform(std::string name, const GLfloat* value) {
    mat4Uniforms[name] = value;

    return *this;
}

Renderable& Renderable::setIntUniform(std::string name, GLint value) {
    intUniforms[name] = value;

    return *this;
}

Renderable& Renderable::draw() {
    vertexArray.bind();
    program.bind();

    for (const auto &u : floatUniforms) {
        program.setFloatUniform(u.first, u.second);
    }

    for (const auto &u : vec3Uniforms) {
        program.setVec3Uniform(u.first, u.second);
    }

    for (const auto &u : mat4Uniforms) {
        program.setMat4Uniform(u.first, u.second);
    }

    for (const auto &u : intUniforms) {
        program.setIntUniform(u.first, u.second);
    }


    if (vertexArray.indexed) {
        glDrawElements(GL_TRIANGLES, vertexArray.numElements, vertexArray.indexType, NULL);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, vertexArray.numElements);
    }

    return *this;
}