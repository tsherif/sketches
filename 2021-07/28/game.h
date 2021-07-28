#ifndef _GAME_H_
#define _GAME_H_

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

// Must be implemented by game, to be used by platform layer.
void init(void);
void update(void);
void draw(void);
void resize(int width, int height);
void mouseClick(int x, int y);
void keyboard(Keyboard* inputKeys);
void controller(Controller* controllerInput);

#endif