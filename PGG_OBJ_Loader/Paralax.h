/// \file Paralax.h
/// \Code that creates the paralax mapped box
/// \author Jamie Agate

#ifndef _PARALAX_H_
#define _PARALAX_H_
//File Includes
#include "GameObject.h"
//Header Contents
class Paralax :
	public GameObject
{
public:
	Paralax(char* _objFile, char* _vertShader, char* _fragShader, char* _texture, char* _specMap, glm::vec3 _lightPos, glm::vec3 _scale, glm::vec3 _pos, Camera* _cam, char* _normalMap, char* _depthMap);//paralax constructor
	~Paralax();//paralax destructor

	void Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix) override;//paralax draw function
private:
	unsigned int m_normalMap;//normal map
	unsigned int m_depthMap;//depth map

	unsigned int LoadTexture(char* _file);//loads normal/depth map
};

#endif // !_PARALAX_H_


