/*********************************************************************************
* The MIT License (MIT)
*
* Copyright (c) 2020 Tarek Sherif
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of
* this software and associated documentation files (the "Software"), to deal in
* the Software without restriction, including without limitation the rights to
* use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
* the Software, and to permit persons to whom the Software is furnished to do so,
* subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
* FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
* COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
* IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**********************************************************************************/

//////////////////////////////////////////////////////
// Example of basic usage of Simple OpenGL 
// Loader with Win32 using SOGL_IMPLEMENTATION_WIN32
//////////////////////////////////////////////////////

#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../../lib/c/simple-opengl-loader.h"

#define CIRCLES_INITIAL_SIZE 32

typedef struct {
    float* data;
    GLuint buffer;
    GLuint itemSize;
    GLenum usage;
} buffer;

typedef struct circle {
    float x;
    float y;
    float color[3];
    float radius;
} circle;

typedef struct {
    buffer offset;
    buffer color;
    buffer radius;
    GLsizei count;
    struct {
        float* data;
        size_t count;
    } storage;
} CircleData;

static struct {
    uint32_t width;
    uint32_t height;
} canvas;

static GLuint pixelSizeLocation;

CircleData circles = {
    .offset = {
        .itemSize = 2,
        .usage = GL_DYNAMIC_DRAW
    },
    .color = {
        .itemSize = 3,
        .usage = GL_DYNAMIC_DRAW
    },
    .radius = {
        .itemSize = 1,
        .usage = GL_DYNAMIC_DRAW
    }
};

void checkStorage(CircleData* circles, size_t count) {
    if (circles->storage.count >= count) {
        return;
    }

    // 2 for offset, 3 for color, 1 for radius
    size_t oldCount = circles->storage.count;
    size_t newCount = oldCount > 0 ? oldCount * 2 : 1;
    while (newCount < count) {
        newCount *= 2;
    }
    float* newData = (float *) malloc(6 * newCount * sizeof(float));

    float* offsetPtr = newData;
    float* colorPtr = offsetPtr + 2 * newCount;
    float* radiusPtr = colorPtr + 3 * newCount;

    if (circles->storage.data) {
        memcpy(offsetPtr, circles->offset.data, oldCount * circles->offset.itemSize * sizeof(float));
        memcpy(colorPtr, circles->color.data, oldCount * circles->color.itemSize * sizeof(float));
        memcpy(radiusPtr, circles->radius.data, oldCount *  circles->radius.itemSize * sizeof(float));
        free(circles->storage.data);
    }

    circles->storage.data = newData;
    circles->storage.count = newCount;
    circles->offset.data = offsetPtr;
    circles->color.data = colorPtr;
    circles->radius.data = radiusPtr;
}

void flushBuffer(buffer* b, GLsizei count) {
    glBindBuffer(GL_ARRAY_BUFFER, b->buffer);
    glBufferData(GL_ARRAY_BUFFER, count * b->itemSize * sizeof(float), b->data, b->usage);
}

float randomRange(float min, float max) {
    float range = max - min;
    return min + ((float) rand() / (RAND_MAX + 1)) * range;
}

void setCircle(CircleData* circles, size_t i, circle* c) {
    size_t pi = 2 * i;
    size_t ci = 3 * i;

    circles->offset.data[pi]       = c->x; 
    circles->offset.data[pi + 1]   = c->y; 
    circles->color.data[ci]        = c->color[0];
    circles->color.data[ci + 1]    = c->color[1];
    circles->color.data[ci + 2]    = c->color[2];
    circles->radius.data[i]        = c->radius;
}

void addCircle(CircleData* circles, float x, float y) {
    checkStorage(circles, circles->count + 1);

    circle c;
    c.x = x;
    c.y = y;
    c.radius = randomRange(2.0f, 20.0f);
    c.color[0] = randomRange(0.0f, 1.0f);
    c.color[1] = randomRange(0.0f, 1.0f);
    c.color[2] = randomRange(0.0f, 1.0f);

    setCircle(circles, circles->count, &c);
    ++circles->count;
}

void init(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    const char* vsSource = "#version 450\n"
    "layout (location=0) in vec2 position;\n"
    "layout (location=1) in vec2 pixelOffset;\n"
    "layout (location=2) in vec3 color;\n"
    "layout (location=3) in float radius;\n"
    "uniform vec2 pixelSize;\n"
    "out vec2 vPosition;\n"
    "out vec3 vColor;\n"
    "out float vRadius;\n"
    "void main() {\n"
    "    vec2 clipOffset = (pixelOffset * pixelSize - 1.0) * vec2(1.0, -1.0);\n"
    "    vPosition = position * radius;\n"
    "    vColor = color;\n"
    "    vRadius = radius;\n"
    "    gl_Position = vec4(vPosition * pixelSize + clipOffset, 0.0, 1.0);\n"
    "}\n";

    const char* fsSource = "#version 450\n"
    "in vec2 vPosition;\n"
    "in vec3 vColor;\n"
    "in float vRadius;\n"
    "uniform vec2 pixelSize;\n"
    "out vec4 fragColor;\n"
    "void main() {\n"
    "    if (length(vPosition) > vRadius) {\n"
    "       discard;\n"
    "    }\n"
    "    fragColor = vec4(vColor, 1.0);\n"
    "}\n";

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
        MessageBox(NULL, L"Program failed to link!", L"FAILURE", MB_OK);
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
        if (result != GL_TRUE) {
            MessageBox(NULL, L"Vertex shader failed to compile!", L"FAILURE", MB_OK);
        }
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
        if (result != GL_TRUE) {
            MessageBox(NULL, L"Fragment shader failed to compile!", L"FAILURE", MB_OK);
        }
    }


    glUseProgram(program);
    pixelSizeLocation = glGetUniformLocation(program, "pixelSize");

    float positions[] = {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        -1.0f, 1.0f,
        1.0f,  1.0f
    };

    checkStorage(&circles, CIRCLES_INITIAL_SIZE);

    GLuint circleArray;
    glGenVertexArrays(1, &circleArray);
    glBindVertexArray(circleArray);

    GLuint instanceBuffers[3];
    glGenBuffers(3, instanceBuffers);

    circles.offset.buffer = instanceBuffers[0];
    circles.color.buffer  = instanceBuffers[1];
    circles.radius.buffer = instanceBuffers[2];

    GLuint positionBuffer;
    glGenBuffers(1, &positionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, circles.offset.buffer);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribDivisor(1, 1);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, circles.color.buffer);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribDivisor(2, 1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, circles.radius.buffer);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribDivisor(3, 1);
    glEnableVertexAttribArray(3);

    srand((unsigned int) time(NULL));
}

void draw(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, circles.count);
}

void resize(int width, int height) {
   glViewport(0, 0, width, height);
   glUniform2f(pixelSizeLocation, 2.0f / width, 2.0f / height);
   draw(); 
}

void mouseClick(int x, int y) {
    addCircle(&circles, (float) x, (float) y);
    flushBuffer(&circles.offset, circles.count);
    flushBuffer(&circles.color, circles.count);
    flushBuffer(&circles.radius, circles.count);
}
