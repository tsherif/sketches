#ifndef _TYPES_H_
#define _TYPES_H_

typedef struct {
	bool left;
	bool right;
	bool up;
	bool down;
	bool space;
	bool ctrl;
	bool changed;
} Keyboard;

typedef struct {
    int x;
    int y;
    bool clicked;
} Mouse;

typedef struct {
	float leftStickX;
	float leftStickY;
	bool aButton;
} Controller;

#endif