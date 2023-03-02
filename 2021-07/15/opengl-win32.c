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

#define WIN32_LEAN_AND_MEAN
#define SOGL_MAJOR_VERSION 4
#define SOGL_MINOR_VERSION 5
#define SOGL_IMPLEMENTATION_WIN32
#include "../../lib/c/simple-opengl-loader.h"
#include <windows.h>
#include <windowsx.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <profileapi.h>
#include <string.h>
#include "create-opengl-window.h"

#define CIRCLES_INITIAL_SIZE 32

struct {
    float* data;
    size_t count;
} circleStorage;

typedef struct circle {
    float x;
    float y;
    float color[3];
    float radius;
} circle;

struct {
    struct {
        uint32_t width;
        uint32_t height;
    } window;
    struct {
        struct {
            float* offset;
            float* color;
            float* radius;
            GLsizei count;
        } circles;
    } gl;
    struct {
        int x;
        int y;
        bool clicked;
    } mouse;
} programState = {
    .window = {
        .width = 800,
        .height = 600
    },
    .gl = {
        .circles = { 0 }
    }
};

void checkStorage(size_t count) {
    if (circleStorage.count >= count) {
        return;
    }

    // 2 for offset, 3 for color, 1 for radius
    size_t newCount = circleStorage.count > 0 ? circleStorage.count * 2 : 1;
    while (newCount < count) {
        newCount *= 2;
    }
    float* newData = (float *) malloc(6 * newCount * sizeof(float));

    float* offsetPtr = newData;
    float* colorPtr = offsetPtr + 2 * newCount;
    float* radiusPtr = colorPtr + 3 * newCount;

    if (circleStorage.data) {
        memcpy(offsetPtr, programState.gl.circles.offset, circleStorage.count * 2 * sizeof(float));
        memcpy(colorPtr, programState.gl.circles.color, circleStorage.count * 3 * sizeof(float));
        memcpy(radiusPtr, programState.gl.circles.radius, circleStorage.count * sizeof(float));
        free(circleStorage.data);
    }

    circleStorage.data = newData;
    circleStorage.count = newCount;
    programState.gl.circles.offset = offsetPtr;
    programState.gl.circles.color = colorPtr;
    programState.gl.circles.radius = radiusPtr;
}

float randomRange(float min, float max) {
    float range = max - min;
    return min + ((float) rand() / (RAND_MAX + 1)) * range;
}

void getCircle(size_t i, circle* c) {
    size_t pi = 2 * i;
    size_t ci = 3 * i;

    c->x        = programState.gl.circles.offset[pi]; 
    c->y        = programState.gl.circles.offset[pi + 1]; 
    c->color[0] = programState.gl.circles.color[ci];
    c->color[1] = programState.gl.circles.color[ci + 1];
    c->color[2] = programState.gl.circles.color[ci + 2];
    c->radius   = programState.gl.circles.radius[i];
}

void setCircle(size_t i, circle* c) {
    size_t pi = 2 * i;
    size_t ci = 3 * i;

    programState.gl.circles.offset[pi]       = c->x; 
    programState.gl.circles.offset[pi + 1]   = c->y; 
    programState.gl.circles.color[ci]        = c->color[0];
    programState.gl.circles.color[ci + 1]    = c->color[1];
    programState.gl.circles.color[ci + 2]    = c->color[2];
    programState.gl.circles.radius[i]        = c->radius;
}

void addCircle(float x, float y) {
    checkStorage(programState.gl.circles.count + 1);

    circle c;
    c.x = x;
    c.y = y;
    c.radius = randomRange(2.0f, 20.0f);
    c.color[0] = randomRange(0.0f, 1.0f);
    c.color[1] = randomRange(0.0f, 1.0f);
    c.color[2] = randomRange(0.0f, 1.0f);

    setCircle(programState.gl.circles.count, &c);
    ++programState.gl.circles.count;
}

////////////////
// WIN32 setup
////////////////

LRESULT CALLBACK winProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_SIZING: {
            RECT clientRect;
            GetClientRect(window, &clientRect); 
            programState.window.width = clientRect.right - clientRect.left;
            programState.window.height = clientRect.bottom - clientRect.top;
            return 0;
        } break;
        case WM_LBUTTONUP: {
            programState.mouse.x = GET_X_LPARAM(lParam);
            programState.mouse.y = GET_Y_LPARAM(lParam);
            programState.mouse.clicked = true;
            return 0;
        } break;
        case WM_CLOSE: {
            PostQuitMessage(0);
            return 0;
        } break;
    }

    return DefWindowProc(window, message, wParam, lParam);
}

int CALLBACK WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int showWindow) {
    HWND window = createOpenGLWindow( &(CreateOpenGLWindowArgs) {
        .title = L"Bouncing Balls OpenGL Win32 Example", 
        .majorVersion = SOGL_MAJOR_VERSION, 
        .minorVersion = SOGL_MINOR_VERSION,
        .winCallback = winProc,
        .width = programState.window.width,
        .height = programState.window.height
    });
    
    if (!sogl_loadOpenGL()) {
        const char **failures = sogl_getFailures();
        while (*failures) {
            char debugMessage[256];
            snprintf(debugMessage, 256, "SOGL WIN32 EXAMPLE: Failed to load function %s\n", *failures);
            OutputDebugStringA(debugMessage);
            failures++;
        }
    }

    srand((unsigned int) time(NULL));

    RECT clientRect;
    GetClientRect(window, &clientRect); 
    programState.window.width = clientRect.right - clientRect.left;
    programState.window.height = clientRect.bottom - clientRect.top;

    ///////////////////////////
    // Set up GL resources
    ///////////////////////////

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
    GLuint colorLocation = glGetUniformLocation(program, "color");
    GLuint pixelSizeLocation = glGetUniformLocation(program, "pixelSize");    

    GLuint circleArray;
    glGenVertexArrays(1, &circleArray);
    glBindVertexArray(circleArray);

    float positions[] = {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        -1.0f, 1.0f,
        1.0f,  1.0f
    };

    checkStorage(CIRCLES_INITIAL_SIZE);

    GLuint positionBuffer;
    glGenBuffers(1, &positionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    GLuint offsetBuffer;
    glGenBuffers(1, &offsetBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, offsetBuffer);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribDivisor(1, 1);
    glEnableVertexAttribArray(1);

    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribDivisor(2, 1);
    glEnableVertexAttribArray(2);

    GLuint radiusBuffer;
    glGenBuffers(1, &radiusBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, radiusBuffer);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribDivisor(3, 1);
    glEnableVertexAttribArray(3);

    ///////////////////
    // Display window
    ///////////////////

    ShowWindow(window, showWindow);
    HDC deviceContext = GetDC(window);

    //////////////////////////////////
    // Start render and message loop
    //////////////////////////////////

    MSG message;
    LARGE_INTEGER startTicks, endTicks, elapsedTime, tickFrequency;
    QueryPerformanceFrequency(&tickFrequency);
    uint32_t ticks = 0;
    float frameTime = 0.0f;
    float totalTime = 0.0f;
    float averageTime = 0.0f;
    float minTime = 10000.0f;
    float maxTime = -10000.0f;
    bool running = true;
    while (running) {
        QueryPerformanceCounter(&startTicks);
        while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&message);
            DispatchMessage(&message);

            if (message.message == WM_QUIT) {
                running = false; 
                break;
            }
        }

        if (programState.mouse.clicked) {
            addCircle((float) programState.mouse.x, (float) programState.mouse.y);
            glBindBuffer(GL_ARRAY_BUFFER, offsetBuffer);
            glBufferData(GL_ARRAY_BUFFER, programState.gl.circles.count * 2 * sizeof(float), programState.gl.circles.offset, GL_DYNAMIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
            glBufferData(GL_ARRAY_BUFFER, programState.gl.circles.count * 3 * sizeof(float), programState.gl.circles.color, GL_DYNAMIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, radiusBuffer);
            glBufferData(GL_ARRAY_BUFFER, programState.gl.circles.count * sizeof(float), programState.gl.circles.radius, GL_DYNAMIC_DRAW);
            programState.mouse.clicked = false;
        }

        glViewport(0, 0, programState.window.width, programState.window.height);
        glUniform2f(pixelSizeLocation, 2.0f / programState.window.width, 2.0f / programState.window.height);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, programState.gl.circles.count);

        //////////////////
        // SWAP BUFFERS
        //////////////////

        SwapBuffers(deviceContext);
        QueryPerformanceCounter(&endTicks);

        elapsedTime.QuadPart = (endTicks.QuadPart - startTicks.QuadPart) * 1000000;
        elapsedTime.QuadPart /= tickFrequency.QuadPart;

        frameTime = elapsedTime.QuadPart / 1000.0f;
        ++ticks;

        totalTime += frameTime;
        averageTime = totalTime / ticks;
        minTime = frameTime < minTime ? frameTime : minTime;
        maxTime = frameTime > maxTime ? frameTime : maxTime;

        if (ticks == 600) {
            char buffer[1024];
            snprintf(buffer, 1024, "Bouncing Balls OpenGL Win32 Example: Frame Time Average: %.2fms, Min: %.2fms, Max: %.2fms", averageTime, minTime, maxTime);
            SetWindowTextA(window, buffer);
            totalTime = 0.0f;
            ticks = 0;
        }
    }

    return (int) message.wParam;
}
