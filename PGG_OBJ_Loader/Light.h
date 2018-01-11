/// \file Light.h
/// \Point light code
/// \author Jamie Agate


#ifndef _LIGHT_H_
#define _LIGHT_H_
//File Includes
#include "GameObject.h"
#include "InputManager.h"
//Header Contents
class Light :
	public GameObject
{
public:
	Light( char* _objFile, char* _vertShader, char* _fragShader, char* _texture, glm::vec3 _lightPos, glm::vec3 _scale, glm::vec3 _pos, InputManager* _input);//light constructor
	~Light();//light destructor

	glm::vec3 GetLightPos() { return m_lightPos; }//returns light position

	void Update(float _deltaT);//updates light

private:
	InputManager* m_input;//input manager
	glm::vec3 m_lightPos;//light position
};

#endif // !_LIGHT_H_


