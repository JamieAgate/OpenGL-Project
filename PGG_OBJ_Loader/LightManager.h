#ifndef _LIGHTMANAGER_H_
#define _LIGHTMANAGER_H_

#include "Light.h"
#include <vector>

class LightManager
{
public:
	LightManager(InputManager* _input);
	~LightManager();

	void AddLight(char* _objFile, char* _vertShader, char* _fragShader, char* _texture, glm::vec3 _lightPos, glm::vec3 _scale);
	void LoadLightPositions();

	glm::vec3 GetLightAt(int _i) { return m_lightPos[_i]; }

	void Update(float _deltaT);
	void Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix);
private:
	std::vector<Light*> m_lightsVector;
	InputManager* m_input;
	glm::vec3 m_lightPos[4];
};

#endif // !_LIGHTMANAGER_H_