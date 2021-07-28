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
#include "platform-interface.h"

PlatformSound* music;

static struct {
    uint16_t width;
    uint16_t height;
} canvas;

// Animations
#define SHIP_CENTER       0
#define SHIP_CENTER_LEFT  1
#define SHIP_LEFT         2
#define SHIP_CENTER_RIGHT 3
#define SHIP_RIGHT        4

#define MAX_BULLETS 256
#define BULLET_VELOCITY (-5.0f)

typedef struct {
    uint8_t frames[32][2];
    uint8_t numFrames;
} Animation;

typedef struct {
    float panelDims[2];
    float sheetDims[2];
    Animation* animations;
    uint8_t numAnimations;
    GLuint texture;
} Sprite;

typedef struct {
    float position[2];
    float velocity[2];
    bool faceLeft;
    uint8_t currentAnimation;
    uint8_t animationTick;
    uint8_t currentSpritePanel[2];
    float spriteScale;
    Sprite* sprite;
} Character;

static Animation shipAnimations[]  = {
    // Center
    {
        .frames = {{2, 0}, {2, 1}},
        .numFrames = 2
    },
    // Center left
    {
        .frames = {{1, 0}, {1, 1}},
        .numFrames = 2
    },
    // Left
    {
        .frames = {{0, 0}, {0, 1}},
        .numFrames = 2
    },
    // Center right
    {
        .frames = {{3, 0}, {3, 1}},
        .numFrames = 2
    },
    // Right
    {
        .frames = {{4, 0}, {4, 1}},
        .numFrames = 2
    }
};

static Sprite shipSprite = {
    .panelDims = { 16.0f, 24.0f },
    .sheetDims = { 5.0f, 2.0f },
    .animations = shipAnimations,
    .numAnimations = sizeof(shipAnimations) / sizeof(shipAnimations[0])
};

static Character ship = {
    .position = { 100.0f, 200.0f },
    .velocity = { 0.0f, 0.0f },
    .spriteScale = 4.0,
    .sprite = &shipSprite
};

static Animation bulletAnimations[]  = {
    {
        .frames = {{0, 0}, {1, 0}},
        .numFrames = 2
    },
    {
        .frames = {{0, 1}, {1, 1}},
        .numFrames = 2
    }
};

static Sprite bulletSprite = {
    .panelDims = { 16.0f, 16.0f },
    .sheetDims = { 2.0f, 2.0f },
    .animations = bulletAnimations,
    .numAnimations = sizeof(bulletAnimations) / sizeof(bulletAnimations[0])
};

static Character bullets[MAX_BULLETS];
static uint16_t numBullets;

static GLuint pixelSizeLocation;
static GLuint panelPixelSizeLocation;
static GLuint spriteSheetLocation;
static GLuint spriteSheetDimensionsLocation;
static GLuint panelIndexLocation;
static GLuint pixelOffsetLocation;
static GLuint spriteScaleLocation;

static void updateAnimationPanel(Character* character) {
    uint8_t* panel = character->sprite->animations[character->currentAnimation].frames[character->animationTick];

    character->currentSpritePanel[0] = panel[0];
    character->currentSpritePanel[1] = panel[1];
}

static void setCharacterAnimation(Character* character, uint8_t animation) {
    if (character->currentAnimation == animation) {
        return;
    }

    character->currentAnimation = animation;
    character->animationTick = 0;
    updateAnimationPanel(character);
}

static void fireBullet(float x, float y) {
    if (numBullets == MAX_BULLETS) {
        return;
    }

    bullets[numBullets].position[0] = x;
    bullets[numBullets].position[1] = y;
    bullets[numBullets].velocity[0] = 0.0f;
    bullets[numBullets].velocity[1] = BULLET_VELOCITY;
    bullets[numBullets].spriteScale = 4.0,
    bullets[numBullets].sprite = &bulletSprite;
    bullets[numBullets].currentAnimation = 1;
    bullets[numBullets].animationTick = 0;

    updateAnimationPanel(&bullets[numBullets]);
    ++numBullets;
}

static void killBullet(uint8_t i) {
    if (i >= numBullets) {
        return;
    }

    bullets[i] = bullets[numBullets - 1];
    --numBullets;
}

void game_init(void) {
    music = platform_loadSound("../../audio/music.wav");

    platform_playSound(music);

    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    ship.position[0] = canvas.width / 2 - ship.sprite->panelDims[0] * ship.spriteScale / 2;
    ship.position[1] = canvas.height - 150.0f;

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
    "    fragColor.rgb *= fragColor.a;\n"
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
    uint8_t *imageData = stbi_load("../../img/ship.png", &imageWidth, &imageHeight, &imageChannels, 4);

    glGenTextures(1, &shipSprite.texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, shipSprite.texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    stbi_image_free(imageData);

    imageData = stbi_load("../../img/laser-bolts.png", &imageWidth, &imageHeight, &imageChannels, 4);

    glGenTextures(1, &bulletSprite.texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, bulletSprite.texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    stbi_image_free(imageData);

    glUniform1i(spriteSheetLocation, 0);

    setCharacterAnimation(&ship, SHIP_CENTER);
}

static int tick = 0;
void game_update(void) {
    ship.position[0] += ship.velocity[0];
    ship.position[1] += ship.velocity[1];

    if (ship.position[0] < 0.0f) {
        ship.position[0] = 0.0f;
    }

    if (ship.position[0] + ship.sprite->panelDims[0] * ship.spriteScale > canvas.width) {
        ship.position[0] = canvas.width - ship.sprite->panelDims[0] * ship.spriteScale;
    }

    if (ship.position[1] < 0.0f) {
        ship.position[1] = 0.0f;
    }

    if (ship.position[1] + ship.sprite->panelDims[1] * ship.spriteScale > canvas.height) {
        ship.position[1] = canvas.height - ship.sprite->panelDims[1] * ship.spriteScale;
    }

    for (uint8_t i = 0; i < numBullets; ++i) {
        bullets[i].position[0] += bullets[i].velocity[0];
        bullets[i].position[1] += bullets[i].velocity[1];

        if (bullets[i].position[1] + bullets[i].sprite->panelDims[1] * bullets[i].spriteScale < 0) {
            killBullet(i);
        }
    }

    if (tick == 0) {
        uint8_t count = ship.sprite->animations[ship.currentAnimation].numFrames;
        ship.animationTick = (ship.animationTick + 1) % count;
        updateAnimationPanel(&ship);
    fireBullet(100.0f, 200.0f);
        

        tick = 40;
    }
    --tick;
}

void game_draw(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBindTexture(GL_TEXTURE_2D, shipSprite.texture);
    glUniform2fv(panelPixelSizeLocation, 1, shipSprite.panelDims);
    glUniform2fv(spriteSheetDimensionsLocation, 1, shipSprite.sheetDims);
    glUniform1f(spriteScaleLocation, ship.spriteScale);
    glUniform2fv(pixelOffsetLocation, 1, ship.position);
    glUniform3f(panelIndexLocation, (float) ship.currentSpritePanel[0], ship.currentSpritePanel[1], (float) ship.faceLeft);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindTexture(GL_TEXTURE_2D, bulletSprite.texture);
    glUniform2fv(panelPixelSizeLocation, 1, bulletSprite.panelDims);
    glUniform2fv(spriteSheetDimensionsLocation, 1, bulletSprite.sheetDims);

    for (uint8_t i = 0; i < numBullets; ++i) {
        glUniform1f(spriteScaleLocation, bullets[i].spriteScale);
        glUniform2fv(pixelOffsetLocation, 1, bullets[i].position);
        glUniform3f(panelIndexLocation, (float) bullets[i].currentSpritePanel[0], bullets[i].currentSpritePanel[1], (float) bullets[i].faceLeft);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
}

void game_resize(int width, int height) {
    canvas.width = width;
    canvas.height = height;
    glViewport(0, 0, width, height);
    glUniform2f(pixelSizeLocation, 2.0f / width, 2.0f / height);
    game_draw(); 
}

void game_keyboard(GameKeyboard* inputKeys) {
    if (inputKeys->left) {
        ship.velocity[0] = -2.0f;
        setCharacterAnimation(&ship, SHIP_LEFT);
    } else if (inputKeys->right) {
        ship.velocity[0] = 2.0f;
        setCharacterAnimation(&ship, SHIP_RIGHT);
    } else {
        ship.velocity[0] = 0.0f;
        setCharacterAnimation(&ship, SHIP_CENTER);
    }

    if (inputKeys->up) {
        ship.velocity[1] = -2.0f;
    } else if (inputKeys->down) {
        ship.velocity[1] = 2.0f;
    } else {
        ship.velocity[1] = 0.0f;
    }
}

void game_controller(GameController* controllerInput) {
    ship.velocity[0] = 2.0f * controllerInput->leftStickX;
    ship.velocity[1] = -2.0f * controllerInput->leftStickY;

    if (ship.velocity[0] < -1.0f) {
        setCharacterAnimation(&ship, SHIP_LEFT);
    } else if (ship.velocity[0] < 0.0f) {
        setCharacterAnimation(&ship, SHIP_CENTER_LEFT);
    } else if (ship.velocity[0] > 1.0f) {
        setCharacterAnimation(&ship, SHIP_RIGHT);
    } else if (ship.velocity[0] > 0.0f) {
        setCharacterAnimation(&ship, SHIP_CENTER_RIGHT);
    } else {
        setCharacterAnimation(&ship, SHIP_CENTER);
    }
}
