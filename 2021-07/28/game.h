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
} GameKeyboard;

typedef struct {
	float leftStickX;
	float leftStickY;
	bool aButton;
} GameController;

// Must be implemented by game, to be used by platform layer.
void game_init(void);
void game_update(void);
void game_draw(void);
void game_resize(int width, int height);
void game_keyboard(GameKeyboard* inputKeys);
void game_controller(GameController* controllerInput);

#endif