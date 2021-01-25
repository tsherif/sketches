#define WIN32_LEAN_AND_MEAN
#define _USE_MATH_DEFINES
#define SOGL_MAJOR_VERSION 4
#define SOGL_MINOR_VERSION 5
#define SOGL_IMPLEMENTATION_WIN32
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
#define WORK_GROUP_SIZE 64
#define WORK_GROUPS 64
#define NUM_PARTICLES (WORK_GROUP_SIZE * WORK_GROUPS)
#define PARTICLE_SIZE 4

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
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    const char* csSource = R"GLSL(#version 450
    layout(std430, binding=0) buffer Position {
        vec4 position[];
    };
    layout(std430, binding=1) buffer Velocity {
        vec4 velocity[];
    };
    layout(std430, binding=2) buffer Mass {
        float mass[];
    };
    layout (local_size_x = 64, local_size_y = 1, local_size_z = 1) in;
    void main() {
        uint index = gl_GlobalInvocationID.x;
        vec3 p = position[index].xyz;
        vec3 v = velocity[index].xyz;
        float m = mass[index];
        vec3 acceleration = vec3(0.0);

        for (uint i = 0; i < position.length(); ++i) {
            vec3 otherP = position[i].xyz;
            float otherM = mass[i];

            vec3 delta = otherP - p;
            float dist = max(0.1, length(delta));
            vec3 dir = normalize(delta);

            float a = (m * otherM) / (dist * dist);
            if (i != index) {
                acceleration += dir * a;
            }
        }
        v += acceleration;
        v *= 0.9999;
        position[index].xyz = p + v;
        velocity[index].xyz = v;
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

    layout(location=0) in vec2 vertexPosition;
    layout(location=1) in vec3 position;
    layout(location=2) in vec3 color;

    layout(binding=1) uniform VertexUniforms {
        vec2 screenDimensions;
        float particleSize;
    };

    layout(location=0) out vec3 particleColor;
    void main() {
        particleColor = color;
        gl_Position = vec4(vertexPosition * particleSize / screenDimensions + position.xy, position.z, 1.0);
    }
    )GLSL";

    const char* fsSource = R"GLSL(#version 450
    layout(location=0) in vec3 diffuseColor;

    out vec4 fragColor;
    void main() {
        float alpha = 0.5;
        fragColor = vec4(diffuseColor * alpha, alpha);
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

    float vertexPositionData[] = {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        -1.0f, 1.0f,
        1.0f, 1.0f
    };
    float* positionData = new float[NUM_PARTICLES * 4];
    float* massData = new float[NUM_PARTICLES];
    float* colorData = new float[NUM_PARTICLES * 3];

    for (int i = 0; i < NUM_PARTICLES; ++i) {
        int vec4i = i * 4;
        int vec3i = i * 3;

        positionData[vec4i] = randomRange(-1.0f, 1.0f);
        positionData[vec4i + 1] = randomRange(-1.0f, 1.0f);
        positionData[vec4i + 2] = randomRange(-1.0f, 1.0f);
        positionData[vec4i + 3] = 1.0f;

        massData[i] = randomRange(0.00001f, 0.0001f);

        colorData[vec3i] = randomRange(0.0f, 1.0f);
        colorData[vec3i + 1] = randomRange(0.0f, 1.0f);
        colorData[vec3i + 2] = randomRange(0.0f, 1.0f);
    }

    GLuint vertexPositionBuffer = 0;
    glGenBuffers(1, &vertexPositionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexPositionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositionData), vertexPositionData, GL_STATIC_DRAW);

    GLuint positionBuffer = 0;
    glGenBuffers(1, &positionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, NUM_PARTICLES * 4 * sizeof(float), positionData, GL_STREAM_COPY);

    GLuint velocityBuffer = 0;
    glGenBuffers(1, &velocityBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, velocityBuffer);
    glBufferData(GL_ARRAY_BUFFER, NUM_PARTICLES * 4 * sizeof(float), NULL, GL_STREAM_COPY);

    GLuint massBuffer = 0;
    glGenBuffers(1, &massBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, massBuffer);
    glBufferData(GL_ARRAY_BUFFER, NUM_PARTICLES * sizeof(float), massData, GL_STATIC_DRAW);

    GLuint colorBuffer = 0;
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, NUM_PARTICLES * 3 * sizeof(float), colorData, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, NULL);

    // COMPUTE BUFFER BINDINGS

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, positionBuffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, velocityBuffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, massBuffer);

    // DRAW BUFFER BINDINGS

    GLuint vertexArray = 0;
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    glBindBuffer(GL_ARRAY_BUFFER, vertexPositionBuffer);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribDivisor(1, 1);
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribDivisor(2, 1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, NULL);

    if (glGetError() != GL_NO_ERROR) {
        MessageBox(NULL, L"Error after buffer set up!", L"FAILURE", MB_OK);
        return 1;
    }

    // UNIFORMS

    float vertexUniformData[4] = {};

    vertexUniformData[0] = WIDTH;
    vertexUniformData[1] = HEIGHT;
    vertexUniformData[2] = PARTICLE_SIZE;

    GLuint vertexUniformBuffer = 0;
    glGenBuffers(1, &vertexUniformBuffer);
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, vertexUniformBuffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(vertexUniformData), vertexUniformData, GL_STATIC_DRAW);

    if (glGetError() != GL_NO_ERROR) {
        MessageBox(NULL, L"Error after uniform set up!", L"FAILURE", MB_OK);
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
        glDispatchCompute(WORK_GROUPS, 1, 1);

        glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

        glBindProgramPipeline(drawPipeline);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, NUM_PARTICLES);

        //////////////////
        // SWAP BUFFERS
        //////////////////

        SwapBuffers(deviceContext);
    }

    return (int) message.wParam;
}