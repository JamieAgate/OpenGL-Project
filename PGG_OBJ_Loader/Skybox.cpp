///  @file Skybox.cpp
///  @brief Code that sets up the cubemap to use for the Skybox

#include "Skybox.h"

Skybox::Skybox(char* _vertShader,char* _fragShader, char* _obj,Camera* _cam)
	: GameObject(_vertShader,_fragShader,_obj,_cam)
{
	//all images for the cubemap
	std::vector<std::string> skyboxImages
	{
		"Skybox/right.bmp",
		"Skybox/left.bmp",
		"Skybox/top.bmp",
		"Skybox/bottom.bmp",
		"Skybox/back.bmp",
		"Skybox/front.bmp"
	};
	m_cubemapTexture = loadCubemap(skyboxImages);//loades all textures of cubemap and creates the texture
	m_material->ChangeTexture(m_cubemapTexture);//sets texture
}

Skybox::~Skybox()
{

}

unsigned int Skybox::loadCubemap(std::vector<std::string> faces)
{
	//generates a gl texture
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	//loads all faces
	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		SDL_Surface *data = SDL_LoadBMP(faces[i].c_str());
		if (data)
		{
			//generates a texture and assigns it to the correct side of the cubemap
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
	//sews all sides of the cubemap together
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;//retruns the texture
}

void Skybox::Draw()
{
	
}
