#define WIN32_LEAN_AND_MEAN
#include <windows.h>

const WCHAR WIN_CLASS_NAME[] = L"CREATEWINDOW_CLASS"; 

LRESULT CALLBACK winProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(window, message, wParam, lParam);
}

int CALLBACK WinMain(HINSTANCE instance, HINSTANCE, LPSTR cmdLine, int show) {
	WNDCLASSEX winClass = {};
	winClass.cbSize = sizeof(winClass);
	winClass.style = CS_HREDRAW | CS_VREDRAW;
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

	ShowWindow(window, show);

	MSG message;
	while (GetMessage(&message, NULL, 0, 0)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return (int) message.wParam;
}