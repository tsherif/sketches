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
#include "../../lib/c/stb_image.h"




#define WIDTH 800
#define HEIGHT 800
#define NUM_PARTICLES 100000

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

    const char* vsSource = R"GLSL(#version 450
    layout(std140) uniform;

    layout(location=0) in vec3 aPosition;
    layout(location=1) in vec3 aVelocity;
    layout(location=2) in vec3 aColor;

    uniform Mass {
        float mass1Factor;
        float mass2Factor;
        float mass3Factor;
        vec4 mass1Position;
        vec4 mass2Position;
        vec4 mass3Position;
    };

    out vec3 vPosition;
    out vec3 vVelocity;
    out vec3 vColor;
    void main() {
        vec3 position = aPosition;
        vec3 velocity = aVelocity;

        vec3 massVec = mass1Position.xyz - position;
        float massDist2 = max(0.01, dot(massVec, massVec));
        vec3 acceleration = mass1Factor * normalize(massVec) / massDist2;

        massVec = mass2Position.xyz - position;
        massDist2 = max(0.01, dot(massVec, massVec));
        acceleration += mass2Factor * normalize(massVec) / massDist2;

        massVec = mass3Position.xyz - position;
        massDist2 = max(0.01, dot(massVec, massVec));
        acceleration += mass3Factor * normalize(massVec) / massDist2;

        velocity += acceleration;
        velocity *= 0.9999;

        vPosition = position + velocity;
        vVelocity = velocity;

        vColor = aColor;
        gl_PointSize = 2.0;
        gl_Position = vec4(position, 1.0);
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

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    const char* transformFeedbackVaryings[] = { "vPosition", "vVelocity" };
    glTransformFeedbackVaryings(program, 2, transformFeedbackVaryings, GL_SEPARATE_ATTRIBS);
    glLinkProgram(program);

    GLint result;
    glGetProgramiv(program, GL_LINK_STATUS, &result);

    if (result != GL_TRUE) {
        MessageBox(NULL, L"Program failed to link!", L"FAILURE", MB_OK);
        return 1;
    }

    glUseProgram(program);

    GLuint massUniformsLocation  = glGetUniformBlockIndex(program, "Mass");
    glUniformBlockBinding(program, massUniformsLocation, 0);

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

    GLuint vertexArrayA = 0;
    glGenVertexArrays(1, &vertexArrayA);
    glBindVertexArray(vertexArrayA);

    GLuint positionBufferA = 0;
    glGenBuffers(1, &positionBufferA);
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferA);
    glBufferData(GL_ARRAY_BUFFER, NUM_PARTICLES * 3 * sizeof(float), positionData, GL_STREAM_COPY);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    GLuint velocityBufferA = 0;
    glGenBuffers(1, &velocityBufferA);
    glBindBuffer(GL_ARRAY_BUFFER, velocityBufferA);
    glBufferData(GL_ARRAY_BUFFER, NUM_PARTICLES * 3 * sizeof(float), NULL, GL_STREAM_COPY);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);

    GLuint colorBuffer = 0;
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, NUM_PARTICLES * 3 * sizeof(float), colorData, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, NULL);

    // Transform feedback handles output
    GLuint transformFeedbackA = 0;
    glGenTransformFeedbacks(1, &transformFeedbackA);
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, transformFeedbackA);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, positionBufferA);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 1, velocityBufferA);

    // Vertex array handles input
    GLuint vertexArrayB = 0;
    glGenVertexArrays(1, &vertexArrayB);
    glBindVertexArray(vertexArrayB);

    GLuint positionBufferB = 0;
    glGenBuffers(1, &positionBufferB);
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferB);
    glBufferData(GL_ARRAY_BUFFER, NUM_PARTICLES * 3 * sizeof(float), NULL, GL_STREAM_COPY);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    GLuint velocityBufferB = 0;
    glGenBuffers(1, &velocityBufferB);
    glBindBuffer(GL_ARRAY_BUFFER, velocityBufferB);
    glBufferData(GL_ARRAY_BUFFER, NUM_PARTICLES * 3 * sizeof(float), NULL, GL_STREAM_COPY);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, NULL);

    // Transform feedback handles output
    GLuint transformFeedbackB = 0;
    glGenTransformFeedbacks(1, &transformFeedbackB);
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, transformFeedbackB);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, positionBufferB);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 1, velocityBufferB);

    glBindVertexArray(NULL);
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, NULL);

    GLuint currentVertexArray = vertexArrayA;
    GLuint currentTransformFeedback = transformFeedbackB;

    if (glGetError() != GL_NO_ERROR) {
        MessageBox(NULL, L"Error after vertex buffer set up!", L"FAILURE", MB_OK);
        return 1;
    }

    // UNIFORMS

    float massUniformData[16] = {};

    massUniformData[0] = randomRange(0.0f, 1.0f / 30000);
    massUniformData[1] = randomRange(0.0f, 1.0f / 30000);
    massUniformData[2] = randomRange(0.0f, 1.0f / 30000);

    massUniformData[4] = randomRange(-1.0f, 1.0f);
    massUniformData[5] = randomRange(-1.0f, 1.0f);
    massUniformData[6] = randomRange(-1.0f, 1.0f);

    massUniformData[8] = randomRange(-1.0f, 1.0f);
    massUniformData[9] = randomRange(-1.0f, 1.0f);
    massUniformData[10] = randomRange(-1.0f, 1.0f);

    massUniformData[12] = randomRange(-1.0f, 1.0f);
    massUniformData[13] = randomRange(-1.0f, 1.0f);
    massUniformData[14] = randomRange(-1.0f, 1.0f);

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

        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vertexArrayA);
        glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, currentTransformFeedback);

        glBeginTransformFeedback(GL_POINTS);
        glDrawArrays(GL_POINTS, 0, NUM_PARTICLES);
        glEndTransformFeedback();

        //////////////////
        // SWAP BUFFERS
        //////////////////

        if (currentVertexArray == vertexArrayA) {
            currentVertexArray = vertexArrayB;
            currentTransformFeedback = transformFeedbackA;
        } else {
            currentVertexArray = vertexArrayA;
            currentTransformFeedback = transformFeedbackB;
        }

        SwapBuffers(deviceContext);
    }

    return (int) message.wParam;
}