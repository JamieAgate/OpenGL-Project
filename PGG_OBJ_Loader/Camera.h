#ifndef CAMERA_H_
#define CAMERA_H_
#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include "InputManager.h"

class Camera
{
public:
	Camera(glm::vec3 _camPos, InputManager* _input);
	~Camera();

	void Update(float _delataT);
	glm::mat4 GetViewMat() { return m_viewMatrix; }
	glm::vec3 GetCamPos() { return m_camPos; }

private:
	InputManager* m_input;
	glm::mat4 m_viewMatrix;

	float m_cameraAngleX, m_cameraAngleY;

	int m_mouseX, m_mouseY;
	glm::vec3 m_camPos;
	glm::vec3 m_camUp;
	glm::vec3 m_camFront;

	void Movement(float _delataT);
};

#endif
