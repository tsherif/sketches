# /wd5105 suppressed because it causes an error in winbase.h
cl /std:c17 /Zi /W3 /WX /wd5105 /D "_UNICODE" /D "UNICODE" /D SOGL_MAJOR_VERSION=4 /D SOGL_MINOR_VERSION=5 /Fesound-effect sound-effect.c win32.c user32.lib gdi32.lib opengl32.lib xinput.lib ole32.lib
 