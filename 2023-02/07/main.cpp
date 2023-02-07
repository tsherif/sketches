#define SOGL_IMPLEMENTATION_WIN32
#define SOGL_MAJOR_VERSION 4
#define SOGL_MINOR_VERSION 5
#define CREATE_OPENGL_WINDOW_IMPLEMENTATION

#include "../../lib/create-opengl-window.h"
#include "../../lib/simple-opengl-loader.h"
#include "../../lib/windows-utils.h"
#include "../../lib/gl-utils.h"
#include <string>
#include "object.h"

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

    Buffer vsSource = {};
    Buffer fsSource = {};

    loadTextFile("./triangle.vert", &vsSource);
    loadTextFile("./triangle.frag", &fsSource);


    GLuint program = createProgram(
        (const char*) vsSource.data,
        (const char*) fsSource.data,
        [](const char* message) {
            MessageBoxA(NULL, message, "FAILURE", MB_OK);
        }
    );

    GLuint triangleArray;
    glGenVertexArrays(1, &triangleArray);
    glBindVertexArray(triangleArray);

    float positions[] = {
        -0.5, -0.5,
        0.5, -0.5,
        0.0, 0.5
    };

    GLuint positionBuffer;
    glGenBuffers(1, &positionBuffer);

    uint8_t colors[] = {
        255, 0, 0,
        0, 255, 0,
        0, 0, 255
    };

    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);

    AttributeBufferDataOpts positionOpts = {};
    positionOpts.attributeIndex = 0;
    positionOpts.vbo = positionBuffer;
    positionOpts.data = positions;
    positionOpts.dataByteLength = sizeof(positions);
    positionOpts.type = GL_FLOAT;
    positionOpts.vectorSize = 2;
    attributeBufferData(&positionOpts);

    AttributeBufferDataOpts colorOpts = {};
    colorOpts.attributeIndex = 1;
    colorOpts.vbo = colorBuffer;
    colorOpts.data = colors;
    colorOpts.dataByteLength = sizeof(colors);
    colorOpts.type = GL_UNSIGNED_BYTE;
    colorOpts.vectorSize = 3;
    colorOpts.normalized = true;
    attributeBufferData(&colorOpts);

    glBindVertexArray(0);

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