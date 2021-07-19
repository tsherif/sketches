#define WIN32_LEAN_AND_MEAN
#define SOGL_IMPLEMENTATION_WIN32
#define CREATE_OPENGL_WINDOW_IMPLEMENTATION
#include <windows.h>
#include <windowsx.h>
#include <xinput.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <profileapi.h>
#include "create-opengl-window.h"
#include "../../lib/simple-opengl-loader.h"
#include "input.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void init(void);
void update(void);
void draw(void);
void resize(int width, int height);
void mouseClick(int x, int y);
void keyboard(Keyboard* inputKeys);
void controller(Controller* controllerInput);

Mouse mouse;
Keyboard inputKeys;
Controller controllerInput;

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
        case WM_KEYDOWN: {
            switch (wParam) {
                case VK_LEFT:    inputKeys.left  = true; break;
                case VK_RIGHT:   inputKeys.right = true; break;
                case VK_UP:      inputKeys.up    = true; break;
                case VK_DOWN:    inputKeys.down  = true; break;
                case VK_SPACE:   inputKeys.space = true; break;
                case VK_CONTROL: inputKeys.ctrl  = true; break;
            }
            return 0;
        } break;
        case WM_KEYUP: {
            switch (wParam) {
                case VK_LEFT:    inputKeys.left  = false; break;
                case VK_RIGHT:   inputKeys.right = false; break;
                case VK_UP:      inputKeys.up    = false; break;
                case VK_DOWN:    inputKeys.down  = false; break;
                case VK_SPACE:   inputKeys.space = false; break;
                case VK_CONTROL: inputKeys.ctrl  = false; break;
            }
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

    XINPUT_STATE controllerState;
    int controllerIndex = -1;

    for (int i = 0; i < XUSER_MAX_COUNT; ++i) {
        if (XInputGetState(i, &controllerState) == ERROR_SUCCESS) {
            controllerIndex = i;
            break;
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

        if (ticks % 200 == 0 && controllerIndex == -1) {
            for (int i = 0; i < XUSER_MAX_COUNT; ++i) {
                if (XInputGetState(i, &controllerState) == ERROR_SUCCESS) {
                    controllerIndex = i;
                    break;
                }
            }
        } else if (controllerIndex > -1) {
            if (XInputGetState(controllerIndex, &controllerState) == ERROR_SUCCESS) {
                float x = controllerState.Gamepad.sThumbLX;
                float y = controllerState.Gamepad.sThumbLY;

                float mag = (float) sqrt(x * x + y * y);
                x /= mag;
                y /= mag;

                if (mag > 32767.0f) {
                    mag = 32767.0f;
                }

                if (mag > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
                    mag -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
                    mag /= 32767.0f - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
                    controllerInput.leftStickX = x * mag;
                    controllerInput.leftStickY = y * mag;
                    char buffer[1024];
                    snprintf(buffer, 1024, "Input: x = %f, y = %f\n", controllerInput.leftStickX, controllerInput.leftStickY);
                    OutputDebugStringA(buffer);
                } else {
                    controllerInput.leftStickX = 0.0f;
                    controllerInput.leftStickY = 0.0f;
                }
                controller(&controllerInput);
            } else {
                controllerIndex = -1;
            }
        }

        if (mouse.clicked) {
            mouseClick(mouse.x, mouse.y);
            mouse.clicked = false;
        }

        // keyboard(&inputKeys);

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
