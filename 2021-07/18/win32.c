#define WIN32_LEAN_AND_MEAN
#define SOGL_IMPLEMENTATION_WIN32
#define CREATE_OPENGL_WINDOW_IMPLEMENTATION
#include <windows.h>
#include <windowsx.h>
#include <stdbool.h>
#include <stdio.h>
#include <profileapi.h>
#include "create-opengl-window.h"
#include "../../lib/simple-opengl-loader.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void init(void);
void update(void);
void draw(void);
void resize(int width, int height);
void mouseClick(int x, int y);

static struct {
    int x;
    int y;
    bool clicked;
} mouse;

LRESULT CALLBACK winProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_SIZING: {
            RECT clientRect;
            GetClientRect(window, &clientRect); 
            HDC deviceContext = GetDC(window);
            resize(clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
            SwapBuffers(deviceContext);
            return 0;
            return 0;
        } break;
        case WM_LBUTTONUP: {
            mouse.x = GET_X_LPARAM(lParam);
            mouse.y = GET_Y_LPARAM(lParam);
            mouse.clicked = true;
            return 0;
        } break;
        case WM_CLOSE: {
            PostQuitMessage(0);
            return 0;
        } break;
    }

    return DefWindowProc(window, message, wParam, lParam);
}

int CALLBACK WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int showWindow) {
    HWND window = createOpenGLWindow( &(CreateOpenGLWindowArgs) {
        .title = L"Drawing Sprites OpenGL Win32 Example", 
        .majorVersion = SOGL_MAJOR_VERSION, 
        .minorVersion = SOGL_MINOR_VERSION,
        .winCallback = winProc,
        .width = WINDOW_WIDTH,
        .height = WINDOW_HEIGHT
    });
    
    if (!sogl_loadOpenGL()) {
        const char **failures = sogl_getFailures();
        while (*failures) {
            char debugMessage[256];
            snprintf(debugMessage, 256, "SOGL: Failed to load function %s\n", *failures);
            OutputDebugStringA(debugMessage);
            failures++;
        }
    }

    init();

    RECT clientRect;
    GetClientRect(window, &clientRect); 
    resize(clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
    
    ///////////////////
    // Display window
    ///////////////////

    ShowWindow(window, showWindow);
    HDC deviceContext = GetDC(window);

    //////////////////////////////////
    // Start render and message loop
    //////////////////////////////////

    MSG message;
    LARGE_INTEGER startTicks, endTicks, elapsedTime, tickFrequency;
    QueryPerformanceFrequency(&tickFrequency);
    uint32_t ticks = 0;
    float frameTime = 0.0f;
    float totalTime = 0.0f;
    float averageTime = 0.0f;
    float minTime = 10000.0f;
    float maxTime = -10000.0f;
    bool running = true;
    while (running) {
        QueryPerformanceCounter(&startTicks);
        int count = 0;
        while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE) && count < 100) {
            TranslateMessage(&message);
            DispatchMessage(&message);

            if (message.message == WM_QUIT) {
                running = false; 
                break;
            }
            count++;
        }

        if (mouse.clicked) {
            mouseClick(mouse.x, mouse.y);
            mouse.clicked = false;
        }

        update();
        draw();

        SwapBuffers(deviceContext);
        QueryPerformanceCounter(&endTicks);

        elapsedTime.QuadPart = (endTicks.QuadPart - startTicks.QuadPart) * 1000000;
        elapsedTime.QuadPart /= tickFrequency.QuadPart;

        frameTime = elapsedTime.QuadPart / 1000.0f;
        ++ticks;

        totalTime += frameTime;
        averageTime = totalTime / ticks;
        minTime = frameTime < minTime ? frameTime : minTime;
        maxTime = frameTime > maxTime ? frameTime : maxTime;

        if (ticks == 600) {
            char buffer[1024];
            snprintf(buffer, 1024, "Drawing Sprites OpenGL Win32 Example: Frame Time Average: %.2fms, Min: %.2fms, Max: %.2fms", averageTime, minTime, maxTime);
            SetWindowTextA(window, buffer);
            totalTime = 0.0f;
            ticks = 0;
        }
    }

    return (int) message.wParam;
}
