// Must be implemented by game, to be used by platform layer.

void init(void);
void update(void);
void draw(void);
void resize(int width, int height);
void mouseClick(int x, int y);
void keyboard(Keyboard* inputKeys);
void controller(Controller* controllerInput);