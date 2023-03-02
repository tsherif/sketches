#define SOGL_MAJOR_VERSION 4
#define SOGL_MAJOR_VERSION 4
#define SOGL_IMPLEMENTATION_WIN32
#define CREATE_OPENGL_WINDOW_IMPLEMENTATION
#define CGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define _USE_MATH_DEFINES
#include "../../lib/c/create-opengl-window.h"
#include "../../lib/c/simple-opengl-loader.h"
#include "../../lib/c/HandmadeMath.h"
#include "../../lib/c/gl-utils.h"
#include "../../lib/c/stb_image.h"
#include "../../lib/c/utils.h"
#include "../../lib/c/windows-utils.h"
#include "../../lib/c/camera-utils.h"

#include <windowsx.h>
#include <stdio.h>
#include <math.h>

#define WIDTH 1024
#define HEIGHT 1024
#define MODEL_DIR "../../models/antique-camera/glTF"

struct {
    float x;
    float y;
    float lastX;
    float lastY;
    float wheelDelta;
    bool buttonDown;
} mouse = {
    .lastX = -1.0f,
    .lastY = -1.0f
};

#define ORBIT_SCALE 0.1f
#define ZOOM_SCALE 1.0f

static LRESULT CALLBACK messageHandler(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_MBUTTONDOWN: 
        case WM_MBUTTONUP:
        case WM_MOUSEMOVE: {
            mouse.x = (float) GET_X_LPARAM(lParam); 
            mouse.y = (float) GET_Y_LPARAM(lParam); 
            mouse.buttonDown = (wParam & MK_LBUTTON) != 0;
            return 0;
        } break;
        case WM_MOUSEWHEEL: {
            mouse.wheelDelta = (float) GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
        } break;
        case WM_CLOSE: {
            PostQuitMessage(0);
            return 0;
        } break;
    }

    return DefWindowProc(window, message, wParam, lParam);
}

int32_t WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int32_t showWindow) {
    
    CreateOpenGLWindowArgs args = { 0 };
    args.title = "PBR Demo"; 
    args.majorVersion = SOGL_MAJOR_VERSION; 
    args.minorVersion = SOGL_MINOR_VERSION;
    args.width = WIDTH;
    args.height = HEIGHT;
    args.winCallback = messageHandler;
    args.msaaSamples = 16;
    args.vsync = true;
    
    HWND window = createOpenGLWindow(&args);

    if (!sogl_loadOpenGL()) {
        OutputDebugStringA("The following OpenGL functions could not be loaded:\n");
        const char **failures = sogl_getFailures();
        while (*failures) {
            OutputDebugStringA(*failures);
            failures++;
        }
        OutputDebugStringA("Failed to load OpenGL functions.\n");
        return 1;
    }

    BasicMesh mesh = { 0 };

    createSphere(&mesh);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbos[3] = { 0 };
    glGenBuffers(3, vbos);
    GLuint indexBuffer = vbos[0];
    GLuint positionBuffer = vbos[1];
    GLuint normalBuffer = vbos[2];

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.elementCount * sizeof(uint16_t), mesh.indices, GL_STATIC_DRAW);

    attributeBufferData(& (AttributeBufferDataOpts) {
        .vbo = positionBuffer,
        .attributeIndex = 0,
        .data = (uint8_t *) mesh.positions,
        .dataByteLength = mesh.vertexCount * 3 * sizeof(float),
        .type = GL_FLOAT,
        .vectorSize = 3
    });

    attributeBufferData(& (AttributeBufferDataOpts) {
        .vbo = normalBuffer,
        .attributeIndex = 1,
        .data = (uint8_t *) mesh.normals,
        .dataByteLength = mesh.vertexCount * 3 * sizeof(float),
        .type = GL_FLOAT,
        .vectorSize = 3
    });

    Buffer vsSource = { 0 };
    loadTextFile("vs.glsl", &vsSource);

    Buffer fsSource = { 0 };
    loadTextFile("fs.glsl", &fsSource);

    GLuint program = createProgram((const char *) vsSource.data, (const char *) fsSource.data, OutputDebugStringA);

    if (!program) {
        return 1;
    }

    glUseProgram(program);

    hmm_mat4 projMatrix = HMM_Perspective(45.0f, (float) WIDTH / HEIGHT, 1.0f, 100.0f);

    hmm_vec3 eyePosition = { 0.0f, 0.0f, 30.0f };
    hmm_vec3 eyeTarget = { 0.0f, 0.0f, 0.0f };
    hmm_vec3 eyeUp = { 0.0f, 1.0f, 0.0f };
    hmm_mat4 viewMatrix = HMM_LookAt(eyePosition, eyeTarget, eyeUp);
    float zoom = HMM_LengthVec3(HMM_SubtractVec3(eyePosition, eyeTarget));
    float minZoom = zoom * 0.1f;
    float maxZoom = zoom * 10.0f;

    hmm_vec3 lightPosition = { 20.0f, 20.0f, 20.0f };
    hmm_vec3 lightDirection = { 0.0f, 0.0f, 1.0f };
    hmm_vec3 headlightPosition = { 5.0f, 5.0f, 0.0f };

    GLuint projLocation = glGetUniformLocation(program, "proj");
    GLuint viewLocation = glGetUniformLocation(program, "view");
    GLuint offsetLocation = glGetUniformLocation(program, "offset");
    GLuint eyeLocation = glGetUniformLocation(program, "eyePosition");
    GLuint lightLocation0 = glGetUniformLocation(program, "lightPositions[0]");
    GLuint lightLocation1 = glGetUniformLocation(program, "lightPositions[1]");
    GLuint lightLocation2 = glGetUniformLocation(program, "lightPositions[2]");
    GLuint lightLocation3 = glGetUniformLocation(program, "lightPositions[3]");

    glUniformMatrix4fv(projLocation, 1, GL_FALSE, (const GLfloat *) &projMatrix);
    glUniform3f(lightLocation0, -10.0f,  10.0f, 10.0f);
    glUniform3f(lightLocation1, 10.0f,  10.0f, 10.0f);
    glUniform3f(lightLocation2, -10.0f, -10.0f, 10.0f);
    glUniform3f(lightLocation3, 10.0f, -10.0f, 10.0f);

    ShowWindow(window, showWindow);
    HDC deviceContext = GetDC(window);
    MSG message = { 0 };

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    int32_t numRows = 7;
    int32_t numCols = 7;
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

        if (mouse.buttonDown) {
            float lastX = mouse.lastX > -1.0f ? mouse.lastX : mouse.x;
            float lastY = mouse.lastY > -1.0f ? mouse.lastY : mouse.y;
            float dx = (lastX - mouse.x) * ORBIT_SCALE;
            float dy = (lastY - mouse.y) * ORBIT_SCALE;

            orbitCamera(&eyePosition, &eyeTarget, &eyeUp, dx, dy);
            
            mouse.lastX = mouse.x;
            mouse.lastY = mouse.y;
        } else {
            mouse.lastX = -1.0f;
            mouse.lastY = -1.0f;
        }

        if (mouse.wheelDelta != 0.0f) {
            zoom -= mouse.wheelDelta * ZOOM_SCALE;

            if (zoom < minZoom) {
                zoom = minZoom;
            }

            if (zoom > maxZoom) {
                zoom = maxZoom;
            }

            zoomCamera(&eyePosition, &eyeTarget, zoom);
        
            mouse.wheelDelta = 0.0f;
        }

        viewMatrix = HMM_LookAt(eyePosition, eyeTarget, eyeUp);
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, (const GLfloat *) &viewMatrix);
        glUniform3fv(eyeLocation, 1, (const GLfloat *) &eyePosition);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (int32_t row = 0; row < numRows; ++row) {
            float y = (row - numRows / 2) * 2.5f;
            for (int32_t col = 0; col < numCols; ++col) {
                float x = (col - numCols / 2) * 2.5f;
                glUniform2f(offsetLocation, x, y);
                glDrawElements(GL_TRIANGLES, mesh.elementCount, GL_UNSIGNED_SHORT, NULL);
            }
        }
        

        SwapBuffers(deviceContext);            
    }

    return 0;
}



