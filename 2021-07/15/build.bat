# /wd5105 suppressed because it causes an error in winbase.h
cl /std:c17 /Zi /W3 /WX /wd5105 /D "_UNICODE" /D "UNICODE" opengl-win32.c create-opengl-window.c user32.lib gdi32.lib opengl32.lib
 