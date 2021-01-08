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

int CALLBACK WinMain(HINSTANCE instance, HINSTANCE, LPSTR cmdLine, int showWindow) {
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
    sprintf(rendererString, "Win32 OpenGL - %s",  glGetString(GL_RENDERER));
    SetWindowTextA(window, rendererString);

    ///////////////////////////
    // Set up GL resources
    ///////////////////////////

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);

    const char* vsSource = R"GLSL(#version 450

    layout(std140, column_major) uniform;
    
    layout(location=0) in vec4 position;
    layout(location=1) in vec3 normal;
    layout(location=2) in vec2 uv;
    
    uniform SceneUniforms {
        mat4 viewProj;
        vec4 eyePosition;
        vec4 lightPosition;
    } uScene;       
    
    uniform mat4 uModel;

    out  vec3 vPosition;
    out  vec2 vUV;
    out  vec3 vNormal;
    void main() {
        vec4 worldPosition = uModel * position;
        vPosition = worldPosition.xyz;
        vUV = uv;
        vNormal = mat3(uModel) * normal;
        gl_Position = uScene.viewProj * worldPosition;
    }
    )GLSL";

    const char* fsSource = R"GLSL(#version 450

    layout(std140, column_major) uniform;

    uniform SceneUniforms {
        mat4 viewProj;
        vec4 eyePosition;
        vec4 lightPosition;
    } uScene;

    uniform sampler2D tex;
    
    in vec3 vPosition;
    in vec2 vUV;
    in vec3 vNormal;

    out vec4 fragColor;
    void main() {
        vec3 color = texture(tex, vUV).rgb;

        vec3 normal = normalize(vNormal);
        vec3 eyeVec = normalize(uScene.eyePosition.xyz - vPosition);
        vec3 incidentVec = normalize(vPosition - uScene.lightPosition.xyz);
        vec3 lightVec = -incidentVec;
        float diffuse = max(dot(lightVec, normal), 0.0);
        float highlight = pow(max(dot(eyeVec, reflect(incidentVec, normal)), 0.0), 100.0);
        float ambient = 0.1;
        fragColor = vec4(color * (diffuse + highlight + ambient), 1.0);
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
    glLinkProgram(program);

    GLint result;
    glGetProgramiv(program, GL_LINK_STATUS, &result);

    if (result != GL_TRUE) {
        MessageBox(NULL, L"Program failed to link!", L"FAILURE", MB_OK);
        return 1;
    }

    glUseProgram(program);

    GLuint sceneUniformsLocation = glGetUniformBlockIndex(program, "SceneUniforms");
    glUniformBlockBinding(program, sceneUniformsLocation, 0);

    GLuint modelMatrixLocation = glGetUniformLocation(program, "uModel");
    GLuint texLocation = glGetUniformLocation(program, "tex");

    // BUFFERS

    float cubePositions[] = {
        //front
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,

        //right
        0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,

        //back
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,

        //left
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,

        //top
        -0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, -0.5f,

        //bottom
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f
    };

    float cubeNormals[] = {
        // front
        0, 0, 1, 
        0, 0, 1, 
        0, 0, 1, 
        0, 0, 1, 
        0, 0, 1, 
        0, 0, 1,

        // right
        1, 0, 0, 
        1, 0, 0, 
        1, 0, 0, 
        1, 0, 0, 
        1, 0, 0, 
        1, 0, 0,

        // back 
        0, 0, -1, 
        0, 0, -1, 
        0, 0, -1, 
        0, 0, -1, 
        0, 0, -1, 
        0, 0, -1, 

        // left
        -1, 0, 0, 
        -1, 0, 0, 
        -1, 0, 0, 
        -1, 0, 0, 
        -1, 0, 0, 
        -1, 0, 0,

        // top 
        0, 1, 0, 
        0, 1, 0, 
        0, 1, 0, 
        0, 1, 0, 
        0, 1, 0, 
        0, 1, 0,

        // bottom
        0, -1, 0, 
        0, -1, 0, 
        0, -1, 0, 
        0, -1, 0, 
        0, -1, 0, 
        0, -1, 0
    };

    float cubeUVs[] = {
        //front
        0, 0,
        1, 0,
        0, 1,
        0, 1,
        1, 0,
        1, 1,

        //right
        0, 0,
        1, 0,
        0, 1,
        0, 1,
        1, 0,
        1, 1,

        //back
        0, 0,
        1, 0,
        0, 1,
        0, 1,
        1, 0,
        1, 1,

        //left
        0, 0,
        1, 0,
        0, 1,
        0, 1,
        1, 0,
        1, 1,

        //top
        0, 0,
        1, 0,
        0, 1,
        0, 1,
        1, 0,
        1, 1,

        //bottom
        0, 0,
        1, 0,
        0, 1,
        0, 1,
        1, 0,
        1, 1
    };

    size_t numVertices = sizeof(cubePositions) / (sizeof(cubePositions[0]) * 3);

    GLuint cubeArray = 0;
    glGenVertexArrays(1, &cubeArray);
    glBindVertexArray(cubeArray);

    GLuint positionBuffer = 0;
    glGenBuffers(1, &positionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubePositions), cubePositions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    GLuint normalBuffer = 0;
    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeNormals), cubeNormals, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);

    GLuint uvBuffer = 0;
    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeUVs), cubeUVs, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(2);

    if (glGetError() != GL_NO_ERROR) {
        MessageBox(NULL, L"Error after vertex buffer set up!", L"FAILURE", MB_OK);
        return 1;
    }

    // UNIFORMS

    glm::mat4 projMatrix = glm::perspective((float) M_PI / 2, (float) WIDTH / HEIGHT, 0.1f, 10.0f);

    glm::vec3 eyePosition(1.0f, 1.0f, 1.0f);
    glm::mat4 viewMatrix = glm::lookAt(eyePosition, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 viewProjMatrix = projMatrix * viewMatrix;

    glm::vec3 lightPosition(1.0f, 1.0f, 0.5f);

    glm::mat4 modelMatrix(1.0f);

    float sceneUniformData[24] = {};
    memcpy(sceneUniformData, &viewProjMatrix, sizeof(viewProjMatrix));
    memcpy(sceneUniformData + 16, &eyePosition, sizeof(eyePosition));
    memcpy(sceneUniformData + 20, &lightPosition, sizeof(lightPosition));

    GLuint sceneUniformBuffer = 0;
    glGenBuffers(1, &sceneUniformBuffer);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, sceneUniformBuffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(sceneUniformData), sceneUniformData, GL_STATIC_DRAW);

    if (glGetError() != GL_NO_ERROR) {
        MessageBox(NULL, L"Error after uniform set up!", L"FAILURE", MB_OK);
        return 1;
    }

    // TEXTURE

    int imgWidth, imgHeight, bpp;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* image = stbi_load("opengl-logo.png", &imgWidth, &imgHeight, &bpp, 4);

    if (!image) {
        MessageBox(NULL, L"Failed to load image!", L"FAILURE", MB_OK);
        return 1;
    }

    GLuint tex = 0;
    glGenTextures(1, &tex);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glUniform1i(texLocation, 0);

    free(image);

    if (glGetError() != GL_NO_ERROR) {
        MessageBox(NULL, L"Error after texture set up!", L"FAILURE", MB_OK);
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
    float angleX = 0.01f;
    float angleY = 0.02f;
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

        modelMatrix = glm::rotate(modelMatrix, angleX, glm::vec3(1.0f, 0.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, angleY, glm::vec3(0.0f, 1.0f, 0.0f));

        glUniformMatrix4fv(modelMatrixLocation, 1, false, glm::value_ptr(modelMatrix));

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, numVertices);
        SwapBuffers(deviceContext);
    }

    return (int) message.wParam;
}