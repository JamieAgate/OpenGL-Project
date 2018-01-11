///  @file InputManager.cpp
///  @brief Code that manages all input into the system

#include "InputManager.h"

InputManager::InputManager()
{
	const Uint8* keys = SDL_GetKeyboardState(&m_numKeys);//gets the keyboard state for the keys

	
	m_currentKeys = new Uint8[m_numKeys];//initialises current keys
	m_prevFrameKeys = new Uint8[m_numKeys];//initialises previous keys
}

InputManager::~InputManager()
{
	delete[] m_currentKeys;//deletes current keys
	delete[] m_prevFrameKeys;//deletes previous keys
}

void InputManager::UpdateKeyboard()
{
	const Uint8* keys = SDL_GetKeyboardState(NULL);//gets keyboard state

	std::memcpy(m_prevFrameKeys, m_currentKeys, m_numKeys);//coppies the old key to previous key
	std::memcpy(m_currentKeys, keys, m_numKeys);//coppies new key to current key
}

void InputManager::UpdateMouse(int* _mouseX, int* _mouseY)
{
	SDL_GetRelativeMouseState(_mouseX,_mouseY);//gets mouse state
}

bool InputManager::WasKeyPressed(SDL_Scancode _key)
{
	if (m_currentKeys[_key] && !m_prevFrameKeys[_key]) { return true; }//retruns true if key was not pressed last frame
	else { return false; }
}

bool InputManager::IsKeyDown(SDL_Scancode _key)
{
	if (m_currentKeys[_key] && m_prevFrameKeys[_key]) { return true; }//returns true if key was pressed last frame
	else { return false; }
}

bool InputManager::WasKeyReleased(SDL_Scancode _key)
{
	if (!m_currentKeys[_key] && m_prevFrameKeys[_key]) { return true; }//returns true if key was released
	else { return false; }
}

bool InputManager::WasLMBPressed()
{
	int mouseX, mouseY;
	if (SDL_GetMouseState(&mouseX, &mouseY) && SDL_BUTTON(SDL_BUTTON_LEFT))//returns true if left mouse button was pressed
	{
		return true;
	}
	else
	{
		return false;
	}
}