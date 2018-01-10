#pragma once
#include "GameObject.h"
class Paralax :
	public GameObject
{
public:
	Paralax(char* _objFile, char* _vertShader, char* _fragShader, char* _texture, char* _specMap, glm::vec3 _lightPos, glm::vec3 _scale, glm::vec3 _pos, Camera* _cam, char* _normalMap, char* _depthMap);
	~Paralax();

	void Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix) override;
private:
	unsigned int m_normalMap;
	unsigned int m_depthMap;

	unsigned int LoadTexture(char* _file);
};

