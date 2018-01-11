///  @file Light.cpp
///  @brief Point light code

#include "Light.h"

Light::Light(char* _objFile, char* _vertShader, char* _fragShader, char* _texture, glm::vec3 _lightPos, glm::vec3 _scale, glm::vec3 _pos, InputManager* _input)
	: GameObject(_objFile,_vertShader,_fragShader,_texture,"" ,_lightPos,_scale, _pos,nullptr)
{
	m_input = _input;//sets input manager
	m_lightPos = _lightPos;//sets lights position
}


Light::~Light()
{

}

void Light::Update(float _deltaT)
{
	//moves light
	float lightSpeed = 2.5f * _deltaT;
	if (m_input->IsKeyDown(SDL_SCANCODE_UP))
	{
		MoveX(lightSpeed);
		m_lightPos.x += lightSpeed;
	}
	if (m_input->IsKeyDown(SDL_SCANCODE_DOWN))
	{
		MoveX(-lightSpeed);
		m_lightPos.x -= lightSpeed;
	}
	if (m_input->IsKeyDown(SDL_SCANCODE_LEFT))
	{
		MoveZ(lightSpeed);
		m_lightPos.y += lightSpeed;
	}
	if (m_input->IsKeyDown(SDL_SCANCODE_RIGHT))
	{
		MoveZ(-lightSpeed);
		m_lightPos.y -= lightSpeed;
	}
	if (m_input->IsKeyDown(SDL_SCANCODE_C))
	{
		MoveY(lightSpeed);
		m_lightPos.z += lightSpeed;
	}
	if (m_input->IsKeyDown(SDL_SCANCODE_Z))
	{
		MoveY(-lightSpeed);
		m_lightPos.z -= lightSpeed;
	}
}

