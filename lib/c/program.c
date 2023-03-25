#include "program.h"
#include "../../lib/c/gl-utils.h"

#define CONTAINER Program_UniformMap
#define TYPE Program_UniformData
#define IMPLEMENTATION_ONLY
#include "../../lib/c/str-map.h"

#define CONTAINER Program_SamplerMap
#define TYPE GLint
#define IMPLEMENTATION_ONLY
#include "../../lib/c/str-map.h"

Program Program_create(Program_CreateOptions* options) {
    Program program =  {
        .handle = createProgram(
            options->vsSource,
            options->fsSource,
            options->logFn
        ),
        .uniformData = Program_UniformMap_create(),
        .samplers = Program_SamplerMap_create()
    };

    GLint numUniforms = 0;

    Program_bind(&program);
    glGetProgramiv(program.handle, GL_ACTIVE_UNIFORMS, &numUniforms);

    for (GLint i = 0; i < numUniforms; ++i) {
        Program_UniformData data = { 0 };
        GLchar name[256] = { 0 };
        glGetActiveUniform(program.handle, i, 256, 0, &data.size, &data.type, name);
        data.location = glGetUniformLocation(program.handle, name);
        Program_UniformMap_set(&program.uniformData, name, data);

        switch (data.type) {
            case GL_SAMPLER_1D: // Fallthrough
            case GL_SAMPLER_2D: // Fallthrough
            case GL_SAMPLER_3D: // Fallthrough
            case GL_SAMPLER_CUBE: // Fallthrough
            case GL_SAMPLER_1D_SHADOW: // Fallthrough
            case GL_SAMPLER_2D_SHADOW: // Fallthrough
            case GL_SAMPLER_1D_ARRAY: // Fallthrough
            case GL_SAMPLER_2D_ARRAY: // Fallthrough
            case GL_SAMPLER_1D_ARRAY_SHADOW: // Fallthrough
            case GL_SAMPLER_2D_ARRAY_SHADOW: // Fallthrough
            case GL_SAMPLER_2D_MULTISAMPLE: // Fallthrough
            case GL_SAMPLER_2D_MULTISAMPLE_ARRAY: // Fallthrough
            case GL_SAMPLER_CUBE_SHADOW: // Fallthrough
            case GL_SAMPLER_BUFFER: // Fallthrough
            case GL_SAMPLER_2D_RECT: // Fallthrough
            case GL_SAMPLER_2D_RECT_SHADOW: // Fallthrough
            case GL_INT_SAMPLER_1D: // Fallthrough
            case GL_INT_SAMPLER_2D: // Fallthrough
            case GL_INT_SAMPLER_3D: // Fallthrough
            case GL_INT_SAMPLER_CUBE: // Fallthrough
            case GL_INT_SAMPLER_1D_ARRAY: // Fallthrough
            case GL_INT_SAMPLER_2D_ARRAY: // Fallthrough
            case GL_INT_SAMPLER_2D_MULTISAMPLE: // Fallthrough
            case GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY: // Fallthrough
            case GL_INT_SAMPLER_BUFFER: // Fallthrough
            case GL_INT_SAMPLER_2D_RECT: // Fallthrough
            case GL_UNSIGNED_INT_SAMPLER_1D: // Fallthrough
            case GL_UNSIGNED_INT_SAMPLER_2D: // Fallthrough
            case GL_UNSIGNED_INT_SAMPLER_3D: // Fallthrough
            case GL_UNSIGNED_INT_SAMPLER_CUBE: // Fallthrough
            case GL_UNSIGNED_INT_SAMPLER_1D_ARRAY: // Fallthrough
            case GL_UNSIGNED_INT_SAMPLER_2D_ARRAY: // Fallthrough
            case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE: // Fallthrough
            case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY: // Fallthrough
            case GL_UNSIGNED_INT_SAMPLER_BUFFER: // Fallthrough
            case GL_UNSIGNED_INT_SAMPLER_2D_RECT: // Fallthrough
            case GL_IMAGE_1D: // Fallthrough
            case GL_IMAGE_2D: // Fallthrough
            case GL_IMAGE_3D: // Fallthrough
            case GL_IMAGE_2D_RECT: // Fallthrough
            case GL_IMAGE_CUBE: // Fallthrough
            case GL_IMAGE_BUFFER: // Fallthrough
            case GL_IMAGE_1D_ARRAY: // Fallthrough
            case GL_IMAGE_2D_ARRAY: // Fallthrough
            case GL_IMAGE_2D_MULTISAMPLE: // Fallthrough
            case GL_IMAGE_2D_MULTISAMPLE_ARRAY: // Fallthrough
            case GL_INT_IMAGE_1D: // Fallthrough
            case GL_INT_IMAGE_2D: // Fallthrough
            case GL_INT_IMAGE_3D: // Fallthrough
            case GL_INT_IMAGE_2D_RECT: // Fallthrough
            case GL_INT_IMAGE_CUBE: // Fallthrough
            case GL_INT_IMAGE_BUFFER: // Fallthrough
            case GL_INT_IMAGE_1D_ARRAY: // Fallthrough
            case GL_INT_IMAGE_2D_ARRAY: // Fallthrough
            case GL_INT_IMAGE_2D_MULTISAMPLE: // Fallthrough
            case GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY: // Fallthrough
            case GL_UNSIGNED_INT_IMAGE_1D: // Fallthrough
            case GL_UNSIGNED_INT_IMAGE_2D: // Fallthrough
            case GL_UNSIGNED_INT_IMAGE_3D: // Fallthrough
            case GL_UNSIGNED_INT_IMAGE_2D_RECT: // Fallthrough
            case GL_UNSIGNED_INT_IMAGE_CUBE: // Fallthrough
            case GL_UNSIGNED_INT_IMAGE_BUFFER: // Fallthrough
            case GL_UNSIGNED_INT_IMAGE_1D_ARRAY: // Fallthrough
            case GL_UNSIGNED_INT_IMAGE_2D_ARRAY: // Fallthrough
            case GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE: // Fallthrough
            case GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY: {
                GLint nextUnit = (GLint) Program_SamplerMap_size(&program.samplers);
                Program_SamplerMap_set(&program.samplers, name, nextUnit);
                glUniform1i(data.location, nextUnit);
            }
        }
    }

    return program;
}

void Program_setVecUniform(Program* program, const char* name, const void* value) {
    if (Program_UniformMap_has(&program->uniformData, name)) {
        Program_bind(program);
        Program_UniformData data = Program_UniformMap_get(&program->uniformData, name);

        switch (data.type) {
            case GL_FLOAT_VEC2: glUniform2fv(data.location, 1, value); break;
            case GL_FLOAT_VEC3: glUniform3fv(data.location, 1, value); break;
            case GL_FLOAT_VEC4: glUniform4fv(data.location, 1, value); break;
            case GL_BOOL_VEC2:  // Fallthrough
            case GL_INT_VEC2: glUniform2iv(data.location, 1, value); break;
            case GL_BOOL_VEC3:  // Fallthrough
            case GL_INT_VEC3: glUniform3iv(data.location, 1, value); break;
            case GL_BOOL_VEC4:  // Fallthrough
            case GL_INT_VEC4: glUniform4iv(data.location, 1, value); break;
            case GL_UNSIGNED_INT_VEC2: glUniform2uiv(data.location, 1, value); break;
            case GL_UNSIGNED_INT_VEC3: glUniform3uiv(data.location, 1, value); break;
            case GL_UNSIGNED_INT_VEC4: glUniform4uiv(data.location, 1, value); break;
            case GL_FLOAT_MAT2: glUniformMatrix2fv(data.location, 1, GL_FALSE, value); break;
            case GL_FLOAT_MAT3: glUniformMatrix3fv(data.location, 1, GL_FALSE, value); break;
            case GL_FLOAT_MAT4: glUniformMatrix4fv(data.location, 1, GL_FALSE, value); break;
            case GL_FLOAT_MAT2x3: glUniformMatrix2x3fv(data.location, 1, GL_FALSE, value); break;
            case GL_FLOAT_MAT2x4: glUniformMatrix2x4fv(data.location, 1, GL_FALSE, value); break;
            case GL_FLOAT_MAT3x2: glUniformMatrix3x2fv(data.location, 1, GL_FALSE, value); break;
            case GL_FLOAT_MAT3x4: glUniformMatrix3x4fv(data.location, 1, GL_FALSE, value); break;
            case GL_FLOAT_MAT4x2: glUniformMatrix4x2fv(data.location, 1, GL_FALSE, value); break;
            case GL_FLOAT_MAT4x3: glUniformMatrix4x3fv(data.location, 1, GL_FALSE, value); break;
        }
    }
}

void Program_setIntUniform(Program* program, const char* name, GLint value) {
    if (Program_UniformMap_has(&program->uniformData, name)) {
        Program_bind(program);
        Program_UniformData data = Program_UniformMap_get(&program->uniformData, name);
        glUniform1i(data.location, value);
    }
}


void Program_bind(Program* program) {
    glUseProgram(program->handle);
}