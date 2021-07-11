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
#include "../../lib/simple-opengl-loader.h"
#include <windows.h>
#include <GL\gl.h>
#include "wglext.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

struct {
    struct {
        uint32_t width;
        uint32_t height;
    } window;
} programState = {
    .window = {
        .width = 800,
        .height = 600
    }
};

float randomRange(float min, float max) {
    float range = max - min;
    return min + ((float) rand() / (RAND_MAX + 1)) * range;
}

/////////////////////////////////////
// WGL loading helper functions 
/////////////////////////////////////

#define DECLARE_WGL_EXT_FUNC(returnType, name, ...) typedef returnType (WINAPI *name##FUNC)(__VA_ARGS__);\
    name##FUNC name = (name##FUNC)0;
#define LOAD_WGL_EXT_FUNC(name) name = (name##FUNC) wglGetProcAddress(#name)

/////////////////////////////////////
// Set up OpenGL function pointers
/////////////////////////////////////

DECLARE_WGL_EXT_FUNC(BOOL, wglChoosePixelFormatARB, HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);
DECLARE_WGL_EXT_FUNC(HGLRC, wglCreateContextAttribsARB, HDC hDC, HGLRC hshareContext, const int *attribList);
DECLARE_WGL_EXT_FUNC(BOOL, wglSwapIntervalEXT, int interval);

////////////////
// WIN32 setup
////////////////

const WCHAR WIN_CLASS_NAME[] = L"OPENGL_WINDOW_CLASS"; 

LRESULT CALLBACK winProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_SIZING: {
            if (glViewport) {
                RECT* bounds = (RECT *) lParam;
                programState.window.width = bounds->right - bounds->left;
                programState.window.height = bounds->bottom - bounds->top;
                glViewport(0, 0, programState.window.width, programState.window.height);
            }
            return 0;
        } break;
        case WM_PAINT: {
            if (glClear) {
                HDC deviceContext = GetDC(window);
                glClear(GL_COLOR_BUFFER_BIT);
                glDrawArrays(GL_TRIANGLES, 0, 3);
                SwapBuffers(deviceContext);
            }
        } break;
        case WM_CLOSE: {
            PostQuitMessage(0);
            return 0;
        } break;
    }

    return DefWindowProc(window, message, wParam, lParam);
}

int CALLBACK WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int showWindow) {



    WNDCLASSEX winClass = {
        .cbSize = sizeof(winClass),
        .style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
        .lpfnWndProc = winProc,
        .hInstance = instance,
        .hIcon = LoadIcon(instance, IDI_APPLICATION),
        .hIconSm = LoadIcon(instance, IDI_APPLICATION),
        .hCursor = LoadCursor(NULL, IDC_ARROW),
        .hbrBackground = (HBRUSH)(COLOR_WINDOW + 1),
        .lpszClassName = WIN_CLASS_NAME
    };

    if (!RegisterClassEx(&winClass)) {
        MessageBox(NULL, L"Failed to register window class!", L"FAILURE", MB_OK);

        return 1;
    }

    ////////////////////////////////////////////////////////////////////
    // Create a dummy window so we can get WGL extension functions
    ////////////////////////////////////////////////////////////////////

    HWND dummyWindow = CreateWindow(WIN_CLASS_NAME, L"DUMMY", WS_OVERLAPPEDWINDOW, 0, 0, 1, 1, NULL,  NULL, instance, NULL);

    if (!dummyWindow) {
        MessageBox(NULL, L"Failed to create window!", L"FAILURE", MB_OK);

        return 1;
    }

    HDC dummyContext = GetDC(dummyWindow);

    PIXELFORMATDESCRIPTOR pfd = {
        .nSize = sizeof(PIXELFORMATDESCRIPTOR),
        .nVersion = 1,
        .dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        .iPixelType = PFD_TYPE_RGBA,        
        .cColorBits = 32,                   
        .cDepthBits = 24,           
        .cStencilBits = 8,                 
        .iLayerType = PFD_MAIN_PLANE
    };
    
    
    int pixelFormat = ChoosePixelFormat(dummyContext, &pfd);
    SetPixelFormat(dummyContext, pixelFormat, &pfd);
    HGLRC dummyGL = wglCreateContext(dummyContext);
    wglMakeCurrent(dummyContext, dummyGL);

    LOAD_WGL_EXT_FUNC(wglChoosePixelFormatARB);
    LOAD_WGL_EXT_FUNC(wglCreateContextAttribsARB);
    LOAD_WGL_EXT_FUNC(wglSwapIntervalEXT);

    if (!wglCreateContextAttribsARB || !wglCreateContextAttribsARB) {
        MessageBox(NULL, L"Didn't get wgl ARB functions!", L"FAILURE", MB_OK);
        return 1;
    }

    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(dummyGL);
    DestroyWindow(dummyWindow);

    /////////////////////////////////////////////
    // Create real window and rendering context
    /////////////////////////////////////////////

    HWND window = CreateWindow(
        WIN_CLASS_NAME,
        L"Simple OpenGL Loader Win32 Example",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        programState.window.width, programState.window.height,
        NULL, 
        NULL,
        instance,
        NULL
    );

    if (!window) {
        MessageBox(NULL, L"Failed to create window!", L"FAILURE", MB_OK);

        return 1;
    }

    HDC deviceContext = GetDC(window);

    const int pixelAttribList[] = {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB, 32,
        WGL_DEPTH_BITS_ARB, 24,
        WGL_STENCIL_BITS_ARB, 8,
        WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
        WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
        WGL_SAMPLES_ARB, 4,
        0
    };

    UINT numFormats;
    BOOL success;
    success = wglChoosePixelFormatARB(deviceContext, pixelAttribList, NULL, 1, &pixelFormat, &numFormats);

    if (!success || numFormats == 0) {
        MessageBox(NULL, L"Didn't get ARB pixel format!", L"FAILURE", MB_OK);
        return 1;
    }
    
    DescribePixelFormat(deviceContext, pixelFormat, sizeof(pfd), &pfd);
    SetPixelFormat(deviceContext, pixelFormat, &pfd);

    const int contextAttribList[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 5,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    };

    HGLRC gl = wglCreateContextAttribsARB(deviceContext, NULL, contextAttribList);

    if (!gl) {
        MessageBox(NULL, L"Didn't get ARB GL context!", L"FAILURE", MB_OK);
        return 1;
    }

    wglMakeCurrent(deviceContext, gl);
    
    if (wglSwapIntervalEXT) {
        wglSwapIntervalEXT(1);
    }
    
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

    ///////////////////////////
    // Set up GL resources
    ///////////////////////////

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    const char* vsSource = "#version 450\n"
    "layout (location=0) in vec2 position;\n"
    "uniform vec2 pixelOffset;\n"
    "uniform vec2 pixelSize;\n"
    "uniform float radius;\n"
    "out vec2 vPosition;\n"
    "void main() {\n"
    "    vec2 clipOffset = (pixelOffset * pixelSize - 1.0) * vec2(1.0, -1.0);\n"
    "    vPosition = position * radius;\n"
    "    gl_Position = vec4(vPosition * pixelSize + clipOffset, 0.0, 1.0);\n"
    "}\n";

    const char* fsSource = "#version 450\n"
    "in vec2 vPosition;\n"
    "uniform vec3 color;\n"
    "uniform vec2 pixelSize;\n"
    "uniform float radius;\n"
    "out vec4 fragColor;\n"
    "void main() {\n"
    "    if (length(vPosition) > radius) {\n"
    "       discard;\n"
    "    }\n"
    "    fragColor = vec4(color, 1.0);\n"
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

    struct {
        float x;
        float y;
        float vx;
        float vy;
        float radius;
    } circle = {
        .x = randomRange(0.0f, (float) programState.window.width),
        .y = randomRange(0.0f, (float) programState.window.height),
        .vx = randomRange(-5.0f, 5.0f),
        .vy = randomRange(-5.0f, 5.0f),
        .radius = randomRange(2.0f, 40.0f)
    };

    glUseProgram(program);
    GLuint colorLocation = glGetUniformLocation(program, "color");
    GLuint pixelSizeLocation = glGetUniformLocation(program, "pixelSize");
    GLuint radiusLocation = glGetUniformLocation(program, "radius");
    GLuint pixelOffsetLocation = glGetUniformLocation(program, "pixelOffset");
    glUniform3f(colorLocation, 1.0f, 0.0f, 0.0f);
    glUniform2f(pixelSizeLocation, 2.0f / programState.window.width, 2.0f / programState.window.height);
    glUniform1f(radiusLocation, circle.radius);


    GLuint circleArray;
    glGenVertexArrays(1, &circleArray);
    glBindVertexArray(circleArray);

    float positions[] = {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        -1.0f, 1.0f,
        1.0f,  1.0f
    };

    GLuint positionBuffer;
    glGenBuffers(1, &positionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    ///////////////////
    // Display window
    ///////////////////

    ShowWindow(window, showWindow);

    //////////////////////////////////
    // Start render and message loop
    //////////////////////////////////

    MSG message;
    bool running = true;
    while (running) {
        while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&message);
            DispatchMessage(&message);

            if (message.message == WM_QUIT) {
                running = false; 
                break;
            }
        }

        circle.x += circle.vx;
        circle.y += circle.vy;

        if (circle.x - circle.radius < 0) {
            circle.x = circle.radius;
            circle.vx *= -1;
        }

        if (circle.x + circle.radius > programState.window.width) {
            circle.x = programState.window.width - circle.radius;
            circle.vx *= -1;
        }

        if (circle.y - circle.radius < 0) {
            circle.y = circle.radius;
            circle.vy *= -1;
        }

        if (circle.y + circle.radius > programState.window.height) {
            circle.y = programState.window.height - circle.radius;
            circle.vy *= -1;
        }

        glClear(GL_COLOR_BUFFER_BIT);
        glUniform2f(pixelOffsetLocation, circle.x, circle.y);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        //////////////////
        // SWAP BUFFERS
        //////////////////

        SwapBuffers(deviceContext);
    }

    return (int) message.wParam;
}
