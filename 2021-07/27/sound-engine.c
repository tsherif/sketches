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
#include "input.h"
#include "platform.h"

#define GRAVITY (0.2f)
#define JUMP_FORCE (-5.0f)

Sound* music;
Sound* jump;

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
} DinoState;

int animations[][2]  = {
    {0, 4},
    {4, 6},
    {10, 3},
    {13, 4},
    {17, 1},
    {18, 6}
};

typedef struct {
    float panelDims[2];
    float sheetDims[2];
    int (* animations)[2];
    int numAnimations;
    GLuint texture;
} Sprite;

static struct {
    float position[2];
    float velocity[2];
    bool faceLeft;
    int currentAnimation;
    int animationTick;
    int currentSpritePanel;
    float spriteScale;
    DinoState state;
    Sprite sprite;
    bool jumping;
} dino = {
    .position = { 100.0f, 200.0f },
    .velocity = { 0.0f, 0.0f },
    .spriteScale = 4.0,
    .sprite = {
        .panelDims = { 24.0f, 24.0f },
        .sheetDims = { 24.0f, 1.0f },
        .animations = animations,
        .numAnimations = sizeof(animations) / sizeof(animations[0])
    }
};

static GLuint pixelSizeLocation;
static GLuint panelPixelSizeLocation;
static GLuint spriteSheetLocation;
static GLuint spriteSheetDimensionsLocation;
static GLuint panelIndexLocation;
static GLuint pixelOffsetLocation;
static GLuint spriteScaleLocation;

void setState(DinoState state) {
    if (dino.state == state) {
        return;
    }

    dino.state = state;

    switch (state) {
        case RUN_LEFT: {
            dino.currentAnimation = 5;
        } break;
        case RUN_RIGHT:{
            dino.currentAnimation = 5;
        } break;
        case WALK_LEFT: {
            dino.currentAnimation = 1;
        } break;
        case WALK_RIGHT: {
            dino.currentAnimation = 1;
        } break;
        case IDLE_LEFT: {
            dino.currentAnimation = 0;
        } break;
        case IDLE_RIGHT:{
            dino.currentAnimation = 0;
        } break;
    }

    dino.animationTick = 0;
}

void init(void) {
    music = loadSound("../../audio/music.wav");
    jump = loadSound("../../audio/jump.wav");

    playSound(music);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    const char* vsSource = "#version 450\n"
    "layout (location=0) in vec2 position;\n"
    "uniform vec2 pixelOffset;\n"
    "uniform vec2 pixelSize;\n"
    "uniform vec2 panelPixelSize;\n"
    "uniform float spriteScale;\n"
    "uniform vec3 panelIndex;\n" // z is whether to flip horizontally
    "uniform vec2 spriteSheetDimensions;\n"
    "out vec2 vUV;\n"
    "void main() {\n"
    "    vec2 uv = position;\n"
    "    if (panelIndex.z == 1.0) uv.x = 1.0 - position.x;\n"
    "    vUV = (uv + panelIndex.xy) / spriteSheetDimensions;\n"
    "    vec2 clipOffset = pixelOffset * pixelSize - 1.0;\n"
    "    gl_Position = vec4((position * panelPixelSize * pixelSize * spriteScale + clipOffset) * vec2(1.0, -1.0), 0.0, 1.0);\n"
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
    spriteScaleLocation = glGetUniformLocation(program, "spriteScale");

    glUniform2fv(panelPixelSizeLocation, 1, dino.sprite.panelDims);
    glUniform2fv(spriteSheetDimensionsLocation, 1, dino.sprite.sheetDims);
    glUniform1f(spriteScaleLocation, dino.spriteScale);

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
    uint8_t *imageData = stbi_load("../../img/dino-sprite.png", &imageWidth, &imageHeight, &imageChannels, 4);

    glGenTextures(1, &dino.sprite.texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, dino.sprite.texture);
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
    dino.velocity[1] += GRAVITY;

    dino.position[0] += dino.velocity[0];
    dino.position[1] += dino.velocity[1];

    if (dino.position[0] < 0.0f) {
        dino.position[0] = 0.0f;
    }

    if (dino.position[0] + dino.sprite.panelDims[0] * dino.spriteScale > canvas.width) {
        dino.position[0] = canvas.width - dino.sprite.panelDims[0] * dino.spriteScale;
    }

    if (dino.position[1] + dino.sprite.panelDims[1] * dino.spriteScale > canvas.height) {
        dino.position[1] = canvas.height - dino.sprite.panelDims[1] * dino.spriteScale;
        dino.jumping = false;
    }

    ++tick;
    if (tick == 20) {
        int start = dino.sprite.animations[dino.currentAnimation][0];
        int count = dino.sprite.animations[dino.currentAnimation][1];
        dino.animationTick = (dino.animationTick + 1) % count;
        dino.currentSpritePanel = start + dino.animationTick;
        tick = 0;
    }
}

void draw(void) {
    glUniform2fv(pixelOffsetLocation, 1, dino.position);
    glUniform3f(panelIndexLocation, (float) dino.currentSpritePanel, 0.0f, (float) dino.faceLeft);
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

    if (inputKeys->space && !dino.jumping) {
        dino.velocity[1] = JUMP_FORCE;
        dino.jumping = true;
        playSound(jump);
    }

    bool running = inputKeys->ctrl;
    if (inputKeys->left) {
        dino.velocity[0] = running ? -2.0f : -1.0f;
        setState(running ? RUN_LEFT : WALK_LEFT);
    } else if (inputKeys->right) {
        dino.velocity[0] = running ? 2.0f : 1.0f;
        setState(running ? RUN_RIGHT : WALK_RIGHT);
    } else {
        dino.velocity[0] = 0.0f;
        setState(dino.faceLeft ? IDLE_LEFT : IDLE_RIGHT);
    }

    if (dino.velocity[0] != 0.0f) {
        dino.faceLeft = dino.velocity[0] < 0.0f;
    }
}

void controller(Controller* controllerInput) {
    dino.velocity[0] = 2.0f * controllerInput->leftStickX;

    if (controllerInput->aButton && !dino.jumping) {
        dino.velocity[1] = JUMP_FORCE;
        dino.jumping = true;
        playSound(jump);
    }

     if (dino.velocity[0] > 1.0f) {
        setState(RUN_RIGHT);
    } else if (dino.velocity[0] < -1.0f) {
        setState(RUN_LEFT);
    } else if (dino.velocity[0] > 0.0f) {
        setState(WALK_RIGHT);
    } else if (dino.velocity[0] < 0.0f) {
        setState(WALK_LEFT);
    } else {
        setState(dino.faceLeft ? IDLE_LEFT : IDLE_RIGHT);
    }

    if (dino.velocity[0] != 0.0f) {
        dino.faceLeft = dino.velocity[0] < 0.0f;
    }
}
