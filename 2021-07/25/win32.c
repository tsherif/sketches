#define WIN32_LEAN_AND_MEAN
#define SOGL_IMPLEMENTATION_WIN32
#define CREATE_OPENGL_WINDOW_IMPLEMENTATION
#include <windows.h>
#include <windowsx.h>
#include <xinput.h>
#include <xaudio2.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <profileapi.h>
#include "../../lib/c/create-opengl-window.h"
#include "../../lib/c/simple-opengl-loader.h"
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

bool gamepadEquals(XINPUT_GAMEPAD* gp1, XINPUT_GAMEPAD* gp2) {
    return gp1->wButtons == gp2->wButtons &&
        gp1->bLeftTrigger == gp2->bLeftTrigger &&
        gp1->bRightTrigger == gp2->bRightTrigger &&
        gp1->sThumbLX == gp2->sThumbLX &&
        gp1->sThumbLY == gp2->sThumbLY &&
        gp1->sThumbRX == gp2->sThumbRX &&
        gp1->sThumbRY == gp2->sThumbRY;
}

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
            inputKeys.changed = true;
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
            inputKeys.changed = true;
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
    XINPUT_GAMEPAD lastGamePadState;

    int controllerIndex = -1;

    for (int i = 0; i < XUSER_MAX_COUNT; ++i) {
        if (XInputGetState(i, &controllerState) == ERROR_SUCCESS) {
            controllerIndex = i;
            break;
        }
    }

    HANDLE audioFile = CreateFileA(
      "../../audio/music.wav",
      GENERIC_READ,
      FILE_SHARE_READ,
      NULL,
      OPEN_EXISTING,
      FILE_ATTRIBUTE_NORMAL,
      NULL
    );

    if (audioFile == INVALID_HANDLE_VALUE) {
        MessageBox(NULL, L"Failed to load audio!", L"FAILURE", MB_OK);
        return 1;
    }

    if (SetFilePointer(audioFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {
        MessageBox(NULL, L"Failed to set file pointer!", L"FAILURE", MB_OK);
        return 1;
    }

    WAVEFORMATEXTENSIBLE waveFormat = { 0 };
    XAUDIO2_BUFFER audioBuffer = { 0 };

    DWORD chunkType;
    DWORD chunkDataSize;
    DWORD fileFormat;

    DWORD fourccRIFF = 'FFIR';
    DWORD fourccDATA = 'atad';
    DWORD fourccFMT  = ' tmf';
    DWORD fourccWAVE = 'EVAW';

    DWORD offset = 0;
    DWORD bytesRead = 0;

    ReadFile(audioFile, &chunkType, sizeof(DWORD), &bytesRead, NULL);     // RIFF chunk
    ReadFile(audioFile, &chunkDataSize, sizeof(DWORD), &bytesRead, NULL); // Data size (for all subchunks)
    ReadFile(audioFile, &fileFormat, sizeof(DWORD), &bytesRead, NULL);    // WAVE format
    ReadFile(audioFile, &chunkType, sizeof(DWORD), &bytesRead, NULL);     // First subchunk (should be 'fmt')
    ReadFile(audioFile, &chunkDataSize, sizeof(DWORD), &bytesRead, NULL); // Data size for format
    ReadFile(audioFile, &waveFormat, chunkDataSize, &bytesRead, NULL);    // Wave format struct
    ReadFile(audioFile, &chunkType, sizeof(DWORD), &bytesRead, NULL);     // Next subchunk (should be 'data')
    ReadFile(audioFile, &chunkDataSize, sizeof(DWORD), &bytesRead, NULL); // Data size for data

    BYTE* audioData = (BYTE *) malloc(chunkDataSize);
    ReadFile(audioFile, audioData, chunkDataSize, &bytesRead, NULL);      // FINALLY!

    audioBuffer.AudioBytes = chunkDataSize;
    audioBuffer.pAudioData = audioData;
    audioBuffer.Flags = XAUDIO2_END_OF_STREAM;

    HRESULT comResult;
    comResult = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (FAILED(comResult)) {
        return 1;
    }

    IXAudio2* xaudio = NULL;
    comResult = XAudio2Create(&xaudio, 0, XAUDIO2_DEFAULT_PROCESSOR );

    if (FAILED(comResult)) {
        return 1;
    }

    IXAudio2MasteringVoice* xaudioMasterVoice = NULL;
    comResult = IXAudio2_CreateMasteringVoice(
        xaudio,
        &xaudioMasterVoice,
        XAUDIO2_DEFAULT_CHANNELS,
        XAUDIO2_DEFAULT_SAMPLERATE,
        0,
        NULL,
        NULL,
        AudioCategory_GameEffects
    );

    if (FAILED(comResult)) {
        return 1;
    }

    IXAudio2SourceVoice* xaudioSourceVoice;
    comResult = IXAudio2_CreateSourceVoice(
        xaudio,
        &xaudioSourceVoice,
        (WAVEFORMATEX*) &waveFormat,
        0,
        XAUDIO2_DEFAULT_FREQ_RATIO,
        NULL,
        NULL,
        NULL
    );

    if (FAILED(comResult)) {
        return 1;
    }

    comResult = IXAudio2SourceVoice_SubmitSourceBuffer(xaudioSourceVoice, &audioBuffer, NULL);

    if (FAILED(comResult)) {
        return 1;
    }

    comResult = IXAudio2SourceVoice_Start(xaudioSourceVoice, 0, XAUDIO2_COMMIT_NOW);

    if (FAILED(comResult)) {
        return 1;
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
                if (!gamepadEquals(&controllerState.Gamepad, &lastGamePadState)) {
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
                    } else {
                        controllerInput.leftStickX = 0.0f;
                        controllerInput.leftStickY = 0.0f;
                    }
                    controller(&controllerInput);
                    lastGamePadState = controllerState.Gamepad;
                }
            } else {
                controllerIndex = -1;
            }
        }

        if (mouse.clicked) {
            mouseClick(mouse.x, mouse.y);
            mouse.clicked = false;
        }

        if (inputKeys.changed) {
            keyboard(&inputKeys);
            inputKeys.changed = false;
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
