#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include <GLES3/gl3.h>

#include <stdint.h>

int main() {
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE gl = 0;
    EmscriptenWebGLContextAttributes attrs = {
        .majorVersion = 2,
        .minorVersion = 0
    };

    double windowWidth = 0.0;
    double windowHeight = 0.0;
    emscripten_get_element_css_size("body", &windowWidth, &windowHeight);
    emscripten_set_canvas_element_size("#canvas", windowWidth, windowHeight);

    gl = emscripten_webgl_create_context("#canvas", &attrs);
    emscripten_webgl_make_context_current(gl);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float positions[] = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.0f, 0.5f
    };

    uint8_t colors[] = {
        255, 0, 0,
        0, 255, 0,
        0, 0, 255
    };

    GLuint vertexArray;
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    GLuint buffers[2] = { 0 };
    glGenBuffers(2, buffers);

    GLuint positionBuffer = buffers[0];
    GLuint colorBuffer = buffers[1];

    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_UNSIGNED_BYTE, GL_TRUE, 0, NULL);
    glEnableVertexAttribArray(1);

    const char* vsSource = 
        "#version 300 es\n"
        "layout(location = 0) in vec4 position;\n"
        "layout(location = 1) in vec3 color;\n"
        "out vec3 vColor;\n"
        "void main() {\n"
        "   vColor = color;\n"
        "   gl_Position = position;\n"
        "}\n";

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vsSource, NULL);
    glCompileShader(vs);

    const char* fsSource = 
        "#version 300 es\n"
        "precision highp float;\n"
        "in vec3 vColor;\n"
        "out vec4 fragColor;\n"
        "void main() {\n"
        "   fragColor = vec4(vColor, 1.0);\n"
        "}\n";

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fsSource, NULL);
    glCompileShader(fs);

    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    glUseProgram(program);

    glDrawArrays(GL_TRIANGLES, 0, 3);


    return 0;
}