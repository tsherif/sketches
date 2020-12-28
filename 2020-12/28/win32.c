#define WIN32_LEAN_AND_MEAN
#include <windows.h>

typedef PROC (*wglGetProcAddressFP)(LPCSTR Arg1);

void *sogl_loadOpenGLFunction(const char *name) {
	static HMODULE module = NULL;
	static wglGetProcAddressFP wglGetProcAddress = NULL;

	if (!module) {
		module = LoadLibrary(L"opengl32.dll");
		wglGetProcAddress = (wglGetProcAddressFP) GetProcAddress(module, "wglGetProcAddress");
	}
    void *fn = (void *)wglGetProcAddress(name);
    if(fn == 0 || (fn == (void *) 0x1) || (fn == (void *) 0x2) || (fn == (void*) 0x3) || (fn == (void *) -1)) {
        fn = (void *) GetProcAddress(module, name);
    }

   	// TODO: Report failures.

    return fn;
}