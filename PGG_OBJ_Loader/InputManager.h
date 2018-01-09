#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_
#include <SDL/SDL.h>
#include <algorithm>

class InputManager
{
public:
	InputManager();
	~InputManager();

	void UpdateKeyboard();
	void UpdateMouse(int *_mouseX, int *_mouseY);

	bool WasKeyPressed(SDL_Scancode _key);
	bool IsKeyDown(SDL_Scancode _key);
	bool WasKeyReleased(SDL_Scancode _key);
	bool WasLMBPressed();


private:
	int numKeys;
	Uint8* currentKeys;
	Uint8* prevFrameKeys;
};

#endif
