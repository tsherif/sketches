#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "glcorearb.h"
#include "wglext.h"
#include <cstdint>

/*
	Resources:
		https://www.khronos.org/opengl/wiki/Creating_an_OpenGL_Context_(WGL)
		https://www.khronos.org/opengl/wiki/Load_OpenGL_Functions
		https://www.khronos.org/registry/OpenGL/extensions/ARB/WGL_ARB_pixel_format.txt
		https://www.khronos.org/registry/OpenGL/extensions/ARB/ARB_multisample.txt
		https://mariuszbartosik.com/opengl-4-x-initialization-in-windows-without-a-framework/
*/

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

#define DECLARE_OPENGL_FUNC(returnType, name, ...) typedef returnType (WINAPI *name##FUNC)(__VA_ARGS__);\
	name##FUNC name = (name##FUNC)0;

#define LOAD_OPENGL_FUNC(name) name = (name##FUNC) getGLFunc(#name)

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
DECLARE_OPENGL_FUNC(GLuint, glCreateShader, GLenum shaderType);
DECLARE_OPENGL_FUNC(void, glShaderSource, GLuint shader, GLsizei count, const GLchar **string, const GLint *length);
DECLARE_OPENGL_FUNC(void, glCompileShader, GLuint shader);
DECLARE_OPENGL_FUNC(GLuint, glCreateProgram);
DECLARE_OPENGL_FUNC(void, glAttachShader, GLuint program, GLuint shader);
DECLARE_OPENGL_FUNC(void, glLinkProgram, GLuint program);
DECLARE_OPENGL_FUNC(void, glUseProgram, GLuint program);
DECLARE_OPENGL_FUNC(void, glGetProgramiv, GLuint program, GLenum pname, GLint *params);
DECLARE_OPENGL_FUNC(void, glGenVertexArrays, GLsizei n, GLuint *arrays);
DECLARE_OPENGL_FUNC(void, glBindVertexArray, GLuint array);
DECLARE_OPENGL_FUNC(void, glGenBuffers, GLsizei n, GLuint *buffers);
DECLARE_OPENGL_FUNC(void, glBindBuffer, GLenum target, GLuint buffer);
DECLARE_OPENGL_FUNC(void, glBufferData, GLenum target, GLsizeiptr size, const void * data, GLenum usage);
DECLARE_OPENGL_FUNC(void, glVertexAttribPointer, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer);
DECLARE_OPENGL_FUNC(void, glEnableVertexAttribArray, GLuint index);
DECLARE_OPENGL_FUNC(void, glDrawArrays, GLenum mode, GLint first, GLsizei count);

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

	////////////////////////////////////////////////////////////////////
	// Create a dummy window so we can get WGL extension functions
	////////////////////////////////////////////////////////////////////

	HWND dummyWindow = CreateWindow(WIN_CLASS_NAME, L"DUMMY", WS_OVERLAPPEDWINDOW, 0, 0, 1, 1, NULL,  NULL, instance, NULL);

	if (!dummyWindow) {
		MessageBox(NULL, L"Failed to create window!", L"FAILURE", MB_OK);

		return 1;
	}

	HDC dummyContext = GetDC(dummyWindow);

	PIXELFORMATDESCRIPTOR pfd = {};
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
	pfd.iPixelType = PFD_TYPE_RGBA,        
	pfd.cColorBits = 32;                   
	pfd.cDepthBits = 24;           
	pfd.cStencilBits = 8;                 
	pfd.iLayerType = PFD_MAIN_PLANE;
	
	int pixelFormat = ChoosePixelFormat(dummyContext, &pfd);
	SetPixelFormat(dummyContext, pixelFormat, &pfd);
	HGLRC dummyGL = wglCreateContext(dummyContext);
	wglMakeCurrent(dummyContext, dummyGL);

	LOAD_OPENGL_FUNC(wglChoosePixelFormatARB);
	LOAD_OPENGL_FUNC(wglCreateContextAttribsARB);

	if (!wglCreateContextAttribsARB || !wglCreateContextAttribsARB) {
		MessageBox(NULL, L"Didn't get wgl ARB functions!", L"FAILURE", MB_OK);
		return 1;
	}

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(dummyGL);
	DestroyWindow(dummyWindow);

	/////////////////////////////////////////////
	// Create real window and rendering context
	/////////////////////////////////////////////

	HWND window = CreateWindow(
		WIN_CLASS_NAME,
		L"WIN32 OPENGL!!!",
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

	const int pixelAttribList[] = {
	    WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
	    WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
	    WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
	    WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
	    WGL_COLOR_BITS_ARB, 32,
	    WGL_DEPTH_BITS_ARB, 24,
	    WGL_STENCIL_BITS_ARB, 8,
	    WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
	    WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
	    WGL_SAMPLES_ARB, 4,
	    0
	};

	UINT numFormats;
	BOOL success;
	success = wglChoosePixelFormatARB(deviceContext, pixelAttribList, NULL, 1, &pixelFormat, &numFormats);

	if (!success || numFormats == 0) {
		MessageBox(NULL, L"Didn't get ARB pixel format!", L"FAILURE", MB_OK);
		return 1;
	}
	
	DescribePixelFormat(deviceContext, pixelFormat, sizeof(pfd), &pfd);
	SetPixelFormat(deviceContext, pixelFormat, &pfd);

	const int contextAttribList[] = {
	    WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
	    WGL_CONTEXT_MINOR_VERSION_ARB, 5,
	    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
	    0
	};

	HGLRC gl = wglCreateContextAttribsARB(deviceContext, NULL, contextAttribList);

	if (!gl) {
		MessageBox(NULL, L"Didn't get ARB GL context!", L"FAILURE", MB_OK);
		return 1;
	}

	wglMakeCurrent(deviceContext, gl);

	///////////////////////////
	// Load OpenGL Functions
	///////////////////////////

	LOAD_OPENGL_FUNC(glClearColor);
	LOAD_OPENGL_FUNC(glClear);
	LOAD_OPENGL_FUNC(glCreateShader);
	LOAD_OPENGL_FUNC(glShaderSource);
	LOAD_OPENGL_FUNC(glCompileShader);
	LOAD_OPENGL_FUNC(glCreateProgram);
	LOAD_OPENGL_FUNC(glAttachShader);
	LOAD_OPENGL_FUNC(glLinkProgram);
	LOAD_OPENGL_FUNC(glGetProgramiv);
	LOAD_OPENGL_FUNC(glUseProgram);
	LOAD_OPENGL_FUNC(glGenVertexArrays);
	LOAD_OPENGL_FUNC(glBindVertexArray);
	LOAD_OPENGL_FUNC(glGenBuffers);
	LOAD_OPENGL_FUNC(glBindBuffer);
	LOAD_OPENGL_FUNC(glBufferData);
	LOAD_OPENGL_FUNC(glVertexAttribPointer);
	LOAD_OPENGL_FUNC(glEnableVertexAttribArray);
	LOAD_OPENGL_FUNC(glDrawArrays);

	///////////////////////////
	// Set up GL resources
	///////////////////////////

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	const char* vsSource = R"GLSL(#version 450
    layout (location=0) in vec4 position;
    layout (location=1) in vec3 color;
    out vec3 vColor;
    void main() {
    	vColor = color;
        gl_Position = position;
    }
    )GLSL";

    const char* fsSource = R"GLSL(#version 450
    in vec3 vColor;
    out vec4 fragColor;
    void main() {
        fragColor = vec4(vColor, 1.0);
    }
    )GLSL";

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vsSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fsSource, NULL);
    glCompileShader(fragmentShader);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint result;
    glGetProgramiv(program, GL_LINK_STATUS, &result);

    if (result != GL_TRUE) {
    	MessageBox(NULL, L"Program failed to link!", L"FAILURE", MB_OK);
    }

    glUseProgram(program);

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
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    uint8_t colors[] = {
        255, 0, 0,
        0, 255, 0,
        0, 0, 255
    };

    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_UNSIGNED_BYTE, GL_TRUE, 0, NULL);
    glEnableVertexAttribArray(1);

    ///////////////////
    // Display window
    ///////////////////

	ShowWindow(window, showWindow);

	//////////////////////////////////
    // Start render and message loop
    //////////////////////////////////

	MSG message;
	while (GetMessage(&message, NULL, 0, 0) > 0) {
		TranslateMessage(&message);
		DispatchMessage(&message);

		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		SwapBuffers(deviceContext);
	}

	return (int) message.wParam;
}