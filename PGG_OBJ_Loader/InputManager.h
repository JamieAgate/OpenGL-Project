/// \file InputManager.h
/// \Code that manages all input into the system
/// \author Jamie Agate

#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_
//File Includes
#include <SDL/SDL.h>
#include <algorithm>
//Header Contents
class InputManager
{
public:
	InputManager();//input manager constructor
	~InputManager();//input manager destructor

	void UpdateKeyboard();//updates the keyboard
	void UpdateMouse(int *_mouseX, int *_mouseY);//updates the mouse

	bool WasKeyPressed(SDL_Scancode _key);//checks if the key was pressed
	bool IsKeyDown(SDL_Scancode _key);//checks if the key is down
	bool WasKeyReleased(SDL_Scancode _key);//checks if the key has been released
	bool WasLMBPressed();//checks if the left mouse button was pressed


private:
	int m_numKeys;//used for copying the keys accros
	Uint8* m_currentKeys;//current frame key pressed
	Uint8* m_prevFrameKeys;//previous frame key pressed
};

#endif
