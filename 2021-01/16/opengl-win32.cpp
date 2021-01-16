#define WIN32_LEAN_AND_MEAN
#define _USE_MATH_DEFINES
#define SOGL_MAJOR_VERSION 4
#define SOGL_MINOR_VERSION 5
#define SOGL_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "../../lib/simple-opengl-loader.h"
#include <windows.h>
#include <cstdint>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "wglext.h"
#include "../../lib/glm/glm.hpp"
#include "../../lib/glm/ext.hpp"
#include "../../lib/stb_image.h"




#define WIDTH 800
#define HEIGHT 800

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
        case WM_CLOSE: {
            PostQuitMessage(0);
            return 0;
        } break;
    }

    return DefWindowProc(window, message, wParam, lParam);
}

float randomRange(float min, float max) {
    float range = max - min;
    return min + ((float) rand() / (RAND_MAX + 1)) * range;
}

int CALLBACK WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int showWindow) {
    WNDCLASSEX winClass = {};
    winClass.cbSize = sizeof(winClass);
    winClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    winClass.lpfnWndProc = winProc;
    winClass.hInstance = instance;
    winClass.hIcon = LoadIcon(instance, IDI_APPLICATION);
    winClass.hIconSm = LoadIcon(instance, IDI_APPLICATION);
    winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    winClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    winClass.lpszClassName = WIN_CLASS_NAME;

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

    PIXELFORMATDESCRIPTOR pfd = {};
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
    pfd.iPixelType = PFD_TYPE_RGBA,        
    pfd.cColorBits = 32;                   
    pfd.cDepthBits = 24;           
    pfd.cStencilBits = 8;                 
    pfd.iLayerType = PFD_MAIN_PLANE;
    
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
        L"WIN32 OPENGL!!!",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        WIDTH, HEIGHT,
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
    wglSwapIntervalEXT(1);
    sogl_loadOpenGL();

    char rendererString[256] = {};
    snprintf(rendererString, 256, "Win32 OpenGL - %s",  glGetString(GL_RENDERER));
    SetWindowTextA(window, rendererString);

    srand((unsigned int) time(NULL));

    ///////////////////////////
    // Set up GL resources
    ///////////////////////////

    glClearColor(0.0, 0.0, 0.0, 1.0);

    const char* csSource = R"GLSL(#version 450
    layout(std430, binding=0) restrict writeonly buffer Position {
        vec2 positions[3];
    };
    layout(std430, binding=1) restrict writeonly buffer Color {
        vec4 colors[3];
    };
    layout(std430, binding=2) restrict writeonly buffer Command {
        uint  count;
        uint  instanceCount;
        uint  first;
        uint  baseInstance;
    } command;
    layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
    void main() {
        positions[0] = vec2(-0.5, -0.5);
        positions[1] = vec2(0.5, -0.5);
        positions[2] = vec2(0.0, 0.5);

        colors[0] = vec4(1.0, 0.0, 0.0, 1.0);
        colors[1] = vec4(0.0, 1.0, 0.0, 1.0);
        colors[2] = vec4(0.0, 0.0, 1.0, 1.0);

        command.count = 3;
        command.instanceCount = 1;
        command.first = 0;
        command.baseInstance = 0;
    }
    )GLSL";

    GLuint computeProgram = glCreateShaderProgramv(GL_COMPUTE_SHADER, 1, &csSource);

    GLint result;
    glGetProgramiv(computeProgram, GL_LINK_STATUS, &result);

    if (result != GL_TRUE) {
        char buffer[256];
        glGetProgramInfoLog(computeProgram, 256, NULL, buffer);
        MessageBoxA(NULL, buffer, "Compute program No LINK", MB_OK);
        return 1;
    }

    GLuint computePipeline = 0;
    glGenProgramPipelines(1, &computePipeline);
    glUseProgramStages(computePipeline, GL_COMPUTE_SHADER_BIT, computeProgram);

    const char* vsSource = R"GLSL(#version 450
    layout(std140) uniform;

    layout(location=0) in vec4 position;
    layout(location=1) in vec4 color;

    layout(location=0) out vec4 vertexColor;
    void main() {
        vertexColor = color;
        gl_Position = position;
    }
    )GLSL";

    const char* fsSource = R"GLSL(#version 450
    layout(location=0) in vec4 surfaceColor;

    out vec4 fragColor;
    void main() {
        fragColor = surfaceColor;
    }
    )GLSL";

    GLuint vertexProgram = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &vsSource);
    glGetProgramiv(vertexProgram, GL_LINK_STATUS, &result);
    if (result != GL_TRUE) {
        char buffer[256];
        glGetProgramInfoLog(vertexProgram, 256, NULL, buffer);
        MessageBoxA(NULL, buffer, "Vertex program failed to link!", MB_OK);
        return 1;
    }

    GLuint fragmentProgram = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &fsSource);
    glGetProgramiv(fragmentProgram, GL_LINK_STATUS, &result);
    if (result != GL_TRUE) {
        char buffer[256];
        glGetProgramInfoLog(fragmentProgram, 256, NULL, buffer);
        MessageBoxA(NULL, buffer, "Fragment program failed to link!", MB_OK);
        return 1;
    }

    GLuint drawPipeline = 0;
    glGenProgramPipelines(1, &drawPipeline);
    glUseProgramStages(drawPipeline, GL_VERTEX_SHADER_BIT, vertexProgram);
    glUseProgramStages(drawPipeline, GL_FRAGMENT_SHADER_BIT, fragmentProgram);

    // BUFFERS

    GLuint positionBuffer = 0;
    glGenBuffers(1, &positionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), NULL, GL_STATIC_DRAW);

    GLuint colorBuffer = 0;
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), NULL, GL_STATIC_DRAW);

    GLuint commandBuffer = 0;
    glGenBuffers(1, &commandBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, commandBuffer);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(GLuint), NULL, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, NULL);

    // COMPUTE BUFFER BINDINGS

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, positionBuffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, colorBuffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, commandBuffer);

    // DRAW BUFFER BINDINGS

    GLuint vertexArray = 0;
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, commandBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, NULL);


    if (glGetError() != GL_NO_ERROR) {
        MessageBox(NULL, L"Error after buffer set up!", L"FAILURE", MB_OK);
        return 1;
    }

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

        glBindProgramPipeline(computePipeline);
        glDispatchCompute(1, 1, 1);

        glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT | GL_COMMAND_BARRIER_BIT);

        glBindProgramPipeline(drawPipeline);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArraysIndirect(GL_TRIANGLES, NULL);

        //////////////////
        // SWAP BUFFERS
        //////////////////

        SwapBuffers(deviceContext);
    }

    return (int) message.wParam;
}