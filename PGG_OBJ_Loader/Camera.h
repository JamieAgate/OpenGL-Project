/// \file Camera.h
/// \Code than handels the camera movement etc
/// \author Jamie Agate


#ifndef CAMERA_H_
#define CAMERA_H_
//File Includes
#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include "InputManager.h"
//Header Contents
class Camera
{
public:
	Camera(glm::vec3 _camPos, InputManager* _input);//Camera default constructor
	~Camera();//Camera destructor

	void Update(float _delataT);//camera update function
	glm::mat4 GetViewMat() { return m_viewMatrix; }//returns view matrix
	glm::vec3 GetCamPos() { return m_camPos; }//retruns the cameras current position
	glm::vec3 GetCamFront() { return m_camFront; }//returns the cameras current from facing direction

private:
	InputManager* m_input;//inputManager
	glm::mat4 m_viewMatrix;//view matrix

	float m_cameraAngleX, m_cameraAngleY;//cameras x and y angles

	int m_mouseX, m_mouseY;//mouse x and y positions
	glm::vec3 m_camPos;//cameras position
	glm::vec3 m_camUp;//cameras up direction
	glm::vec3 m_camFront;//cameras front direction

	void Movement(float _delataT);//function that moves the camera
};

#endif
