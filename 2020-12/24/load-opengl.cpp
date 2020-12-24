#define WIN32_LEAN_AND_MEAN
#include <windows.h>

const WCHAR WIN_CLASS_NAME[] = L"OPENGL_WINDOW_CLASS"; 

typedef BOOL (*wglChoosePixelFormatARBFunc)(
	HDC hdc,
	const int *piAttribIList,
	const FLOAT *pfAttribFList,
	UINT nMaxFormats,
	int *piFormats,
	UINT *nNumFormats
);
wglChoosePixelFormatARBFunc wglChoosePixelFormatARB;

LRESULT CALLBACK winProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_CLOSE: {
			PostQuitMessage(0);
			return 0;
		} break;
	}

	return DefWindowProc(window, message, wParam, lParam);
}

int CALLBACK WinMain(HINSTANCE instance, HINSTANCE, LPSTR cmdLine, int show) {
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
		L"We made a window!",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
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

	HGLRC gl = wglCreateContext(deviceContext);

	BOOL success = wglMakeCurrent(deviceContext, gl);

	HMODULE opengl32 = LoadLibrary(L"opengl32.dll");
	wglChoosePixelFormatARB = (wglChoosePixelFormatARBFunc) GetProcAddress(opengl32, "wglChoosePixelFormatARB");

	if (wglChoosePixelFormatARB) {
		MessageBox(NULL, L"Got wglChoosePixelFormatARB from dll!", L"SUCCESS", MB_OK);
	} else {
		wglChoosePixelFormatARB = (wglChoosePixelFormatARBFunc) wglGetProcAddress("wglChoosePixelFormatARB");
	
		if (wglChoosePixelFormatARB) {
			MessageBox(NULL, L"Got wglChoosePixelFormatARB from ARB!", L"SUCCESS", MB_OK);
		}
	}

	MSG message;
	while (GetMessage(&message, NULL, 0, 0) > 0) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return (int) message.wParam;
}