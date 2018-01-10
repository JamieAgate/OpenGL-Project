#include "Paralax.h"



Paralax::Paralax(char* _objFile, char* _vertShader, char* _fragShader, char* _texture, char* _specMap, glm::vec3 _lightPos, glm::vec3 _scale, glm::vec3 _pos, Camera* _cam, char* _normalMap, char* _depthMap) :
	GameObject(_objFile,_vertShader,_fragShader,_texture,_specMap,_lightPos,_scale,_pos,_cam)
{
	m_normalMap = LoadTexture(_normalMap);
	m_depthMap = LoadTexture(_depthMap);
}

Paralax::~Paralax()
{

}

unsigned int Paralax::LoadTexture(char* _file)
{
	SDL_Surface *image = SDL_LoadBMP(_file);

	if (!image) // Check it worked
	{
		std::cerr << "WARNING: could not load BMP image: " << _file << std::endl;
	}

	// Create OpenGL texture
	unsigned int texName = 0;
	glGenTextures(1, &texName);

	glBindTexture(GL_TEXTURE_2D, texName);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// By default, OpenGL mag filter is linear
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// By default, OpenGL min filter will use mipmaps
	// We therefore either need to tell it to use linear or generate a mipmap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// SDL loads images in BGR order
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_BGR, GL_UNSIGNED_BYTE, image->pixels);

	SDL_FreeSurface(image);

	return texName;
}

void Paralax::Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix)
{
	int shaderProg = _material->GetShaderProgram();

	glUseProgram(shaderProg);

	glActiveTexture(GL_TEXTURE5);
	glUniform1i(glGetUniformLocation(shaderProg, "normalMap"), 5);
	glBindTexture(GL_TEXTURE_2D, m_normalMap);

	glActiveTexture(GL_TEXTURE6);
	glUniform1i(glGetUniformLocation(shaderProg, "depthMap"), 6);
	glBindTexture(GL_TEXTURE_2D, m_depthMap);



	GameObject::Draw(viewMatrix, projMatrix);
}