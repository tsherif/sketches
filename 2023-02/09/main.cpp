#define SOGL_IMPLEMENTATION_WIN32
#define SOGL_MAJOR_VERSION 4
#define SOGL_MINOR_VERSION 5
#define CREATE_OPENGL_WINDOW_IMPLEMENTATION

#include "../../lib/c/create-opengl-window.h"
#include "../../lib/c/simple-opengl-loader.h"
#include "../../lib/c/windows-utils.h"
#include "../../lib/c/gl-utils.h"
#include <string>
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
    CreateOpenGLWindowArgs windowArgs = {};
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
            std::string debugMessage("SOGL WIN32 EXAMPLE: Failed to load function ");
            debugMessage += *failures;
            debugMessage += "\n";
            OutputDebugStringA(debugMessage.c_str());
            failures++;
        }
    }

    ///////////////////////////
    // Set up GL resources
    ///////////////////////////

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    DataBuffer vsSource = {};
    DataBuffer fsSource = {};

    loadTextFile("./triangle.vert", &vsSource);
    loadTextFile("./triangle.frag", &fsSource);

    Program program(vsSource.cdata, fsSource.cdata);

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

    Buffer positionBuffer = Buffer()
        .data(positions, sizeof(positions));
    
    Buffer colorBuffer = Buffer()
        .data(colors, sizeof(colors));

    VertexArray triangleArray = VertexArray()
        .vertexBuffer(0, positionBuffer, GL_FLOAT, 2)
        .vertexBuffer(1, colorBuffer, GL_UNSIGNED_BYTE, 3, true);

    Object triangle(triangleArray, program, 3);


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
        
        triangle.draw();

        SwapBuffers(deviceContext);
    }

    return (int) message.wParam;


}