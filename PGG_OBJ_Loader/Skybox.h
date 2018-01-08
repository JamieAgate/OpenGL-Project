#ifndef SKYBOX_H_
#define SKYBOX_H_

#include <SDL\SDL.h>
#include <vector>
#include <string>
#include <iostream>

#include "glew.h"
#include "GameObject.h"
#include "Camera.h"

class Skybox : public GameObject
{
public:
	Skybox(char* _vertShader, char* _fragShader, char* _obj, Camera* _cam);
	~Skybox();

	unsigned int loadCubemap(std::vector<std::string> faces);

	void Draw();

private:
	unsigned int cubemapTexture;
};

#endif

