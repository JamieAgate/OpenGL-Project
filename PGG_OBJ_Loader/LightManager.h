/// \file LightManager.h
/// \Code that manages all lights in the system
/// \author Jamie Agate

#ifndef _LIGHTMANAGER_H_
#define _LIGHTMANAGER_H_
//File Includes
#include "Light.h"
#include <vector>
//Header Contents
class LightManager
{
public:
	LightManager(InputManager* _input);//light manager constructor
	~LightManager();//light manager destructor

	void AddLight(char* _objFile, char* _vertShader, char* _fragShader, char* _texture, glm::vec3 _lightPos, glm::vec3 _scale);//adds a light to the vector
	void LoadLightPositions();//adds the light positions to the light array

	glm::vec3 GetLightAt(int _i) { return m_lightPos[_i]; }//gets the light in the array at a _i

	void Update(float _deltaT);//updates all lights
	void Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix);//draws all lights
private:
	std::vector<Light*> m_lightsVector;//vector that stores all lights
	InputManager* m_input;//input manager
	glm::vec3 m_lightPos[4];//light array
};

#endif // !_LIGHTMANAGER_H_