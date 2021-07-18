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

#define STB_IMAGE_IMPLEMENTATION
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "../../lib/simple-opengl-loader.h"
#include "../../lib/stb_image.h"
#include "types.h"

static struct {
    uint32_t width;
    uint32_t height;
} canvas;

typedef enum {
    IDLE_RIGHT,
    IDLE_LEFT,
    WALK_RIGHT,
    WALK_LEFT,
    RUN_RIGHT,
    RUN_LEFT
} spriteState;

int animations[][2]  = {
    {0, 4},
    {4, 6},
    {10, 3},
    {13, 4},
    {17, 1},
    {18, 6}
};

static struct {
    float position[2];
    float velocity[2];
    bool faceLeft;
    int animationPanel;
    int panelIndex;
    int currentAnimation;
    float panelDims[2];
    float spriteSheetDims[2];
    int numAnimations;
    int (* animations)[2];
    spriteState state;
} sprite = {
    .position = { 100.0f, 200.0f },
    .velocity = { 0.0f, 0.0f },
    .panelDims = { 96.0f, 96.0f },
    .spriteSheetDims = { 24.0f, 1.0f },
    .animations = animations,
    .numAnimations = sizeof(animations) / sizeof(animations[0])
};

static GLuint pixelSizeLocation;
static GLuint panelPixelSizeLocation;
static GLuint spriteSheetLocation;
static GLuint spriteSheetDimensionsLocation;
static GLuint panelIndexLocation;
static GLuint pixelOffsetLocation;

void setState(spriteState state) {
    if (sprite.state == state) {
        return;
    }

    sprite.state = state;

    switch (state) {
        case RUN_LEFT: {
            sprite.velocity[0] = -2.0f;
            sprite.faceLeft = true;
            sprite.currentAnimation = 5;
        } break;
        case RUN_RIGHT:{
            sprite.velocity[0] = 2.0f;
            sprite.faceLeft = false;
            sprite.currentAnimation = 5;
        } break;
        case WALK_LEFT: {
            sprite.velocity[0] = -1.0f;
            sprite.faceLeft = true;
            sprite.currentAnimation = 1;
        } break;
        case WALK_RIGHT: {
            sprite.velocity[0] = 1.0f;
            sprite.faceLeft = false;
            sprite.currentAnimation = 1;
        } break;
        case IDLE_LEFT: {
            sprite.velocity[0] = 0.0f;
            sprite.faceLeft = true;
            sprite.currentAnimation = 0;
        } break;
        case IDLE_RIGHT:{
            sprite.velocity[0] = 0.0f;
            sprite.faceLeft = false;
            sprite.currentAnimation = 0;
        } break;
    }

    sprite.animationPanel = 0;
}


void init(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    const char* vsSource = "#version 450\n"
    "layout (location=0) in vec2 position;\n"
    "uniform vec2 pixelOffset;\n"
    "uniform vec2 pixelSize;\n"
    "uniform vec2 panelPixelSize;\n"
    "uniform vec3 panelIndex;\n" // z is whether to flip horizontally
    "uniform vec2 spriteSheetDimensions;\n"
    "out vec2 vUV;\n"
    "void main() {\n"
    "    vec2 uv = position;\n"
    "    if (panelIndex.z == 1.0) uv.x = 1.0 - position.x;\n"
    "    vUV = (uv + panelIndex.xy) / spriteSheetDimensions;\n"
    "    vec2 clipOffset = pixelOffset * pixelSize - 1.0;\n"
    "    gl_Position = vec4((position * panelPixelSize * pixelSize + clipOffset) * vec2(1.0, -1.0), 0.0, 1.0);\n"
    "}\n";

    const char* fsSource = "#version 450\n"
    "in vec2 vUV;\n"
    "uniform sampler2D spriteSheet;\n"
    "out vec4 fragColor;\n"
    "void main() {\n"
    "    fragColor = texture(spriteSheet, vUV);\n"
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
    panelPixelSizeLocation = glGetUniformLocation(program, "panelPixelSize");
    spriteSheetLocation = glGetUniformLocation(program, "spriteSheet");
    spriteSheetDimensionsLocation = glGetUniformLocation(program, "spriteSheetDimensions");
    panelIndexLocation = glGetUniformLocation(program, "panelIndex");
    pixelOffsetLocation = glGetUniformLocation(program, "pixelOffset");

    glUniform2fv(panelPixelSizeLocation, 1, sprite.panelDims);
    glUniform2fv(spriteSheetDimensionsLocation, 1, sprite.spriteSheetDims);

    float positions[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f,  1.0f
    };

    GLuint spriteArray;
    glGenVertexArrays(1, &spriteArray);
    glBindVertexArray(spriteArray);

    GLuint positionBuffer;
    glGenBuffers(1, &positionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    int imageWidth, imageHeight, imageChannels;
    uint8_t *imageData = stbi_load("dino-sprite.png", &imageWidth, &imageHeight, &imageChannels, 4);

    GLuint spriteTexture;
    glGenTextures(1, &spriteTexture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, spriteTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    stbi_image_free(imageData);

    glUniform1i(spriteSheetLocation, 0);

    setState(IDLE_RIGHT);
}

static int tick = 0;
void update(void) {
    sprite.position[0] += sprite.velocity[0];
    sprite.position[1] += sprite.velocity[1];

    if (sprite.position[0] < 0.0f) {
        sprite.position[0] = 0.0f;
        setState(IDLE_LEFT);
    }

    if (sprite.position[0] + sprite.panelDims[0] > canvas.width) {
        sprite.position[0] = canvas.width - sprite.panelDims[0];
        setState(IDLE_RIGHT);
    }


    ++tick;
    if (tick == 20) {
        int start = sprite.animations[sprite.currentAnimation][0];
        int count = sprite.animations[sprite.currentAnimation][1];
        sprite.animationPanel = (sprite.animationPanel + 1) % count;
        sprite.panelIndex = start + sprite.animationPanel;
        tick = 0;
    }

    glUniform2fv(pixelOffsetLocation, 1, sprite.position);
    glUniform3f(panelIndexLocation, (float) sprite.panelIndex, 0.0f, (float) sprite.faceLeft);
}

void draw(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void resize(int width, int height) {
    canvas.width = width;
    canvas.height = height;
    glViewport(0, 0, width, height);
    glUniform2f(pixelSizeLocation, 2.0f / width, 2.0f / height);
    draw(); 
}

void mouseClick(int x, int y) {
}

void keyboard(Keyboard* inputKeys) {
    spriteState currentState = sprite.state;
    bool running = inputKeys->ctrl;
    if (inputKeys->left) {
        setState(running ? RUN_LEFT : WALK_LEFT);
    } else if (inputKeys->right) {
        setState(running ? RUN_RIGHT : WALK_RIGHT);
    } else {
        setState(sprite.faceLeft ? IDLE_LEFT : IDLE_RIGHT);
    }
}
