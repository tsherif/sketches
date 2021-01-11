#define WIN32_LEAN_AND_MEAN
#define _USE_MATH_DEFINES
#define SOGL_MAJOR_VERSION 4
#define SOGL_MINOR_VERSION 5
#define SOGL_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "simple-opengl-loader.h"
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
#define WORK_GROUP_SIZE 256
#define WORK_GROUPS 1024
#define NUM_PARTICLES (WORK_GROUP_SIZE * WORK_GROUPS)

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
    layout(std140, binding=0) buffer Position {
        vec4 position[];
    };
    layout(std140, binding=1) buffer Velocity {
        vec4 velocity[];
    };
    layout(std140, binding=0) uniform Mass {
        vec4 mass1Position;
        vec4 mass2Position;
        vec4 mass3Position;
        float mass1Factor;
        float mass2Factor;
        float mass3Factor;
    };
    layout (local_size_x = 256, local_size_y = 1, local_size_z = 1) in;
    void main() {
        uint index = gl_GlobalInvocationID.x;
        vec3 p = position[index].xyz;
        vec3 v = velocity[index].xyz;
        vec3 massVec = mass1Position.xyz - p;
        float massDist2 = max(0.01, dot(massVec, massVec));
        vec3 acceleration = mass1Factor * normalize(massVec) / massDist2;
        massVec = mass2Position.xyz - p;
        massDist2 = max(0.01, dot(massVec, massVec));
        acceleration += mass2Factor * normalize(massVec) / massDist2;
        massVec = mass3Position.xyz - p;
        massDist2 = max(0.01, dot(massVec, massVec));
        acceleration += mass3Factor * normalize(massVec) / massDist2;
        v += acceleration;
        v *= 0.9999;
        position[index].xyz = p + v;
        velocity[index].xyz = v;
    }
    )GLSL";

    GLuint computeShader = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(computeShader, 1, &csSource, NULL);
    glCompileShader(computeShader);

    GLint result;
    glGetShaderiv(computeShader, GL_COMPILE_STATUS, &result);

    if (result != GL_TRUE) {
        char buffer[256];
        glGetShaderInfoLog(computeShader, 256, NULL, buffer);
        MessageBoxA(NULL, buffer, "Compute Shader No COMPILE", MB_OK);
        return 1;
    }

    GLuint computeProgram = glCreateProgram();
    glAttachShader(computeProgram, computeShader);
    glLinkProgram(computeProgram);

    glGetProgramiv(computeProgram, GL_LINK_STATUS, &result);

    if (result != GL_TRUE) {
        char buffer[256];
        glGetProgramInfoLog(computeProgram, 256, NULL, buffer);
        MessageBoxA(NULL, buffer, "Compute program No LINK", MB_OK);
        return 1;
    }

    // GLuint massUniformsLocation  = glGetUniformBlockIndex(computeProgram, "Mass");
    // glUniformBlockBinding(computeProgram, massUniformsLocation, 2);

    const char* vsSource = R"GLSL(#version 450
    layout(std140) uniform;

    layout(location=0) in vec3 aPosition;
    layout(location=1) in vec3 aColor;

    out vec3 vColor;
    void main() {
        vColor = aColor;
        gl_PointSize = 2.0;
        gl_Position = vec4(aPosition, 1.0);
    }
    )GLSL";

    const char* fsSource = R"GLSL(#version 450
    in vec3 vColor;

    out vec4 fragColor;
    void main() {
        float alpha = 0.5;
        fragColor = vec4(vColor * alpha, alpha);
    }
    )GLSL";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vsSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fsSource, NULL);
    glCompileShader(fragmentShader);

    GLuint drawProgram = glCreateProgram();
    glAttachShader(drawProgram, vertexShader);
    glAttachShader(drawProgram, fragmentShader);
    glLinkProgram(drawProgram);

    glGetProgramiv(drawProgram, GL_LINK_STATUS, &result);

    if (result != GL_TRUE) {
        MessageBox(NULL, L"Draw program failed to link!", L"FAILURE", MB_OK);
        return 1;
    }

    // BUFFERS

    float* positionData = new float[NUM_PARTICLES * 3];
    float* colorData = new float[NUM_PARTICLES * 3];

    for (int i = 0; i < NUM_PARTICLES; ++i) {
        int vec3i = i * 3;

        positionData[vec3i] = randomRange(-1.0f, 1.0f);
        positionData[vec3i + 1] = randomRange(-1.0f, 1.0f);
        positionData[vec3i + 2] = randomRange(-1.0f, 1.0f);

        colorData[vec3i] = randomRange(0.0f, 1.0f);
        colorData[vec3i + 1] = randomRange(0.0f, 1.0f);
        colorData[vec3i + 2] = randomRange(0.0f, 1.0f);
    }

    GLuint positionBuffer = 0;
    glGenBuffers(1, &positionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, NUM_PARTICLES * 3 * sizeof(float), positionData, GL_STREAM_COPY);

    GLuint velocityBuffer = 0;
    glGenBuffers(1, &velocityBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, velocityBuffer);
    glBufferData(GL_ARRAY_BUFFER, NUM_PARTICLES * 3 * sizeof(float), NULL, GL_STREAM_COPY);

    GLuint colorBuffer = 0;
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, NUM_PARTICLES * 3 * sizeof(float), colorData, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, NULL);

    // COMPUTE BUFFER BINDINGS

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, positionBuffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, velocityBuffer);

    // DRAW BUFFER BINDINGS

    GLuint vertexArray = 0;
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, NULL);
    glBindVertexArray(NULL);

    if (glGetError() != GL_NO_ERROR) {
        MessageBox(NULL, L"Error after buffer set up!", L"FAILURE", MB_OK);
        return 1;
    }

    // UNIFORMS

    float massUniformData[16] = {};

    massUniformData[0] = randomRange(-1.0f, 1.0f);
    massUniformData[1] = randomRange(-1.0f, 1.0f);
    massUniformData[2] = randomRange(-1.0f, 1.0f);

    massUniformData[4] = randomRange(-1.0f, 1.0f);
    massUniformData[5] = randomRange(-1.0f, 1.0f);
    massUniformData[6] = randomRange(-1.0f, 1.0f);

    massUniformData[8] = randomRange(-1.0f, 1.0f);
    massUniformData[9] = randomRange(-1.0f, 1.0f);
    massUniformData[10] = randomRange(-1.0f, 1.0f);

    massUniformData[12] = randomRange(0.0f, 1.0f / 30000);
    massUniformData[13] = randomRange(0.0f, 1.0f / 30000);
    massUniformData[14] = randomRange(0.0f, 1.0f / 30000);

    GLuint massUniformBuffer = 0;
    glGenBuffers(1, &massUniformBuffer);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, massUniformBuffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(massUniformData), massUniformData, GL_STATIC_DRAW);

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

        glUseProgram(computeProgram);
        glDispatchCompute(WORK_GROUPS, 1, 1);

        glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

        glUseProgram(drawProgram);
        glBindVertexArray(vertexArray);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_POINTS, 0, NUM_PARTICLES);
        glBindVertexArray(NULL);

        //////////////////
        // SWAP BUFFERS
        //////////////////

        SwapBuffers(deviceContext);
    }

    return (int) message.wParam;
}