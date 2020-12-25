#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <GL\gl.h>
#include "wglext.h"

void *getGLFunc(const char *name) {
  	void *fn = (void *)wglGetProcAddress(name);
  	if(fn == 0 || (fn == (void *) 0x1) || (fn == (void *) 0x2) || (fn == (void*) 0x3) || (fn == (void *) -1)) {
    	HMODULE module = LoadLibraryA("opengl32.dll");
    	fn = (void *)GetProcAddress(module, name);
  	}

  	if (!fn) {
  		MessageBox(NULL, L"Failed to get function!", L"FAILURE", MB_OK);
  	}

  	return fn;
}

#define DECLARE_OPENGL_FUNC(returnType, name, ...) typedef returnType (WINAPI *name##FUNC)(__VA_ARGS__)
#define LOAD_OPENGL_FUNC(name)	name##FUNC name = (name##FUNC) getGLFunc(#name)

DECLARE_OPENGL_FUNC(BOOL, wglChoosePixelFormatARB, 
	HDC hdc,
	const int *piAttribIList,
	const FLOAT *pfAttribFList,
	UINT nMaxFormats,
	int *piFormats,
	UINT *nNumFormats
);
DECLARE_OPENGL_FUNC(HGLRC, wglCreateContextAttribsARB, HDC hDC, HGLRC hshareContext, const int *attribList);
DECLARE_OPENGL_FUNC(void, glClearColor, GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
DECLARE_OPENGL_FUNC(void, glClear, GLbitfield mask);

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

	HWND window = CreateWindow(
		WIN_CLASS_NAME,
		L"OPENGL!!!",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 500,
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

	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
		PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
		32,                   // Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                   // Number of bits for the depthbuffer
		8,                    // Number of bits for the stencilbuffer
		0,                    // Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	int pixelFormat = ChoosePixelFormat(deviceContext, &pfd);

	SetPixelFormat(deviceContext, pixelFormat, &pfd);

	HGLRC dummyGL = wglCreateContext(deviceContext);

	wglMakeCurrent(deviceContext, dummyGL);

	LOAD_OPENGL_FUNC(wglChoosePixelFormatARB);
	LOAD_OPENGL_FUNC(wglCreateContextAttribsARB);

	if (!wglCreateContextAttribsARB) {
		MessageBox(NULL, L"Didn't get wglCreateContextAttribsARB!", L"FAILURE", MB_OK);
		return 1;
	}

	const int pixelAttribList[] = {
	    WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
	    WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
	    WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
	    WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
	    WGL_COLOR_BITS_ARB, 32,
	    WGL_DEPTH_BITS_ARB, 24,
	    WGL_STENCIL_BITS_ARB, 8,
	    0, // End
	};

	UINT numFormats;
	BOOL success;
	success = wglChoosePixelFormatARB(deviceContext, pixelAttribList, NULL, 1, &pixelFormat, &numFormats);

	if (!success) {
		MessageBox(NULL, L"Didn't get wglChoosePixelFormatARB pixel format!", L"FAILURE", MB_OK);
		return 1;
	}

	const int contextAttribList[] = {
	    WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
	    WGL_CONTEXT_MINOR_VERSION_ARB, 5,
	    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
	    0, // End
	};

	SetPixelFormat(deviceContext, pixelFormat, &pfd);
	HGLRC gl = wglCreateContextAttribsARB(deviceContext, NULL, contextAttribList);

	if (!gl) {
		MessageBox(NULL, L"Didn't get wglCreateContextAttribsARB context!", L"FAILURE", MB_OK);
		return 1;
	}


	wglMakeCurrent(deviceContext, gl);

	LOAD_OPENGL_FUNC(glClearColor);
	LOAD_OPENGL_FUNC(glClear);

	ShowWindow(window, showWindow);

	MSG message;
	while (GetMessage(&message, NULL, 0, 0) > 0) {
		TranslateMessage(&message);
		DispatchMessage(&message);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		SwapBuffers(deviceContext);
	}

	return (int) message.wParam;
}