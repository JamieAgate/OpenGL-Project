///  @file LightManager.cpp
///  @brief Code that manages all lights in the system

#include "LightManager.h"

LightManager::LightManager(InputManager* _input)
{
	m_input = _input;//sets input manager
}


LightManager::~LightManager()
{
	//delets all light
	for each(Light* l in m_lightsVector)
	{
		delete l;
	}
	m_lightsVector.clear();
}

void LightManager::AddLight(char* _objFile, char* _vertShader, char* _fragShader, char* _texture, glm::vec3 _lightPos, glm::vec3 _scale)
{
	m_lightsVector.push_back(new Light(_objFile, _vertShader, _fragShader, _texture, _lightPos, _scale, _lightPos,m_input));//adds newlight to vector
}

void LightManager::LoadLightPositions()
{
	//adds the lights positions to the light pos array
	for (int i = 0; i < m_lightsVector.size(); i++)
	{
		m_lightPos[i] = m_lightsVector.at(i)->GetLightPos();
	}
}

void LightManager::Update(float _deltaT)
{
	//updates all lights
	for each(Light* l in m_lightsVector)
	{
		l->Update(_deltaT);
	}
}

void LightManager::Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix)
{
	//draws all lights
	for each(Light* l in m_lightsVector)
	{
		l->Draw(viewMatrix, projMatrix);
	}
}
