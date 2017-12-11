#pragma once
#include "GameObject.h"
#include "InputManager.h"
class Light :
	public GameObject
{
public:
	Light( char* _objFile, char* _vertShader, char* _fragShader, char* _texture, glm::vec3 _lightPos, glm::vec3 _scale, glm::vec3 _pos, InputManager* _input);
	~Light();

	glm::vec3 GetLightPos() { return m_lightPos; }

	void Update(float _deltaT);

private:
	InputManager* m_input;
	glm::vec3 m_lightPos;
};

