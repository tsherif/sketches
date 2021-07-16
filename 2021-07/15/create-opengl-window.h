#ifndef CREATE_OPENGL_WINDOW_H
#define CREATE_OPENGL_WINDOW_H
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

typedef struct {
	TCHAR* title;
	int majorVersion;
	int minorVersion;
	WNDPROC winCallback;
	int width;
	int height;
} CreateOpenGLWindowArgs;

HWND createOpenGLWindow(CreateOpenGLWindowArgs* args);

#endif