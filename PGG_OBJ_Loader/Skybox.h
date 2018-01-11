/// \file Skybox.h
/// \Code that sets up the cubemap to use for the Skybox
/// \author Jamie Agate

#ifndef SKYBOX_H_
#define SKYBOX_H_
//File Includes
#include <SDL\SDL.h>
#include <vector>
#include <string>
#include <iostream>

#include "glew.h"
#include "GameObject.h"
#include "Camera.h"
//Header Contents
class Skybox : public GameObject
{
public:
	Skybox(char* _vertShader, char* _fragShader, char* _obj, Camera* _cam);//skybox constructor
	~Skybox();//skybox destructor

	unsigned int loadCubemap(std::vector<std::string> faces);//loads the cubemap

	void Draw();//draws the cubemap

private:
	unsigned int m_cubemapTexture;//cubemap texture
};

#endif

