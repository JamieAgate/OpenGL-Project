#include "Skybox.h"

Skybox::Skybox(char* _vertShader,char* _fragShader, char* _obj,Camera* _cam)
	: GameObject(_vertShader,_fragShader,_obj,_cam)
{
	std::vector<std::string> skyboxImages
	{
		"Skybox/right.bmp",
		"Skybox/left.bmp",
		"Skybox/top.bmp",
		"Skybox/bottom.bmp",
		"Skybox/back.bmp",
		"Skybox/front.bmp"
	};
	cubemapTexture = loadCubemap(skyboxImages);
	_material->ChangeTexture(cubemapTexture);
}

Skybox::~Skybox()
{

}

unsigned int Skybox::loadCubemap(std::vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		SDL_Surface *data = SDL_LoadBMP(faces[i].c_str());
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, data->w, data->h, 0, GL_RGB, GL_UNSIGNED_BYTE, data->pixels
			);
			SDL_FreeSurface(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			SDL_FreeSurface(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

void Skybox::Draw()
{
	glDepthMask(GL_FALSE);
	glDepthMask(GL_TRUE);
}
