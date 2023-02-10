#define SOGL_IMPLEMENTATION_WIN32
#define SOGL_MAJOR_VERSION 4
#define SOGL_MINOR_VERSION 5
#define CREATE_OPENGL_WINDOW_IMPLEMENTATION

#include "../../lib/create-opengl-window.h"
#include "../../lib/simple-opengl-loader.h"
#include "../../lib/windows-utils.h"
#include "../../lib/gl-utils.h"
#include <stdio.h>
#include "program.h"
#include "object.h"
#include "buffer.h"
#include "vertex-array.h"

LRESULT CALLBACK winProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CLOSE: {
            PostQuitMessage(0);
            return 0;
        } break;
    }

    return DefWindowProc(window, message, wParam, lParam);
}

int CALLBACK WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int showWindow) {
    CreateOpenGLWindowArgs windowArgs = { 0 };
    windowArgs.title = "OpenGL C++"; 
    windowArgs.majorVersion = SOGL_MAJOR_VERSION; 
    windowArgs.minorVersion = SOGL_MINOR_VERSION;
    windowArgs.winCallback = winProc;
    windowArgs.width = 800;
    windowArgs.height = 800;
    HWND window = createOpenGLWindow(&windowArgs);
    
    if (!sogl_loadOpenGL()) {
        const char **failures = sogl_getFailures();
        while (*failures) {
            char debugMessage[1024];
            snprintf(debugMessage, 1024, "SOGL WIN32 EXAMPLE: Failed to load function %s\n", *failures);
            OutputDebugStringA(debugMessage);
            failures++;
        }
    }

    ///////////////////////////
    // Set up GL resources
    ///////////////////////////

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    DataBuffer vsSource = { 0 };
    DataBuffer fsSource = { 0 };

    loadTextFile("./triangle.vert", &vsSource);
    loadTextFile("./triangle.frag", &fsSource);

    Program program = Program_create(vsSource.cdata, fsSource.cdata, 0);

    float positions[] = {
        -0.5, -0.5,
        0.5, -0.5,
        0.0, 0.5
    };

    uint8_t colors[] = {
        255, 0, 0,
        0, 255, 0,
        0, 0, 255
    };

    Buffer positionBuffer = Buffer_create();
    Buffer_data(&positionBuffer, positions, sizeof(positions));
    
    Buffer colorBuffer = Buffer_create();
    Buffer_data(&colorBuffer, colors, sizeof(colors));
   
    VertexArray triangleArray = VertexArray_create();
    VertexArray_vertexBuffer(&triangleArray, 0, &positionBuffer, GL_FLOAT, 2, false);
    VertexArray_vertexBuffer(&triangleArray, 1, &colorBuffer, GL_UNSIGNED_BYTE, 3, true);

    Object triangle = Object_create(&triangleArray, &program, 3);

    ///////////////////
    // Display window
    ///////////////////

    ShowWindow(window, showWindow);
    HDC deviceContext = GetDC(window);

    //////////////////////////////////
    // Start render and message loop
    //////////////////////////////////

    MSG message;
    while (GetMessage(&message, NULL, 0, 0) > 0) {
        TranslateMessage(&message);
        DispatchMessage(&message);

        glClear(GL_COLOR_BUFFER_BIT);
        
        Object_draw(&triangle);

        SwapBuffers(deviceContext);
    }

    return (int) message.wParam;


}