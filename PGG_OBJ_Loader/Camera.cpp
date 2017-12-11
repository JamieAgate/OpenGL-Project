#include "Camera.h"

Camera::Camera(glm::vec3 _camPos, InputManager* _input)
{
	m_input = _input;
	m_cameraAngleX = 270.0f;
	m_cameraAngleY = 0.0f;
	m_mouseX = 0;
	m_mouseY = 0;
	m_camPos = _camPos;

	m_viewMatrix = glm::translate(glm::mat4(1), _camPos);
	m_camFront = { 0.0f,0.0f,-1.0f };
	m_camUp = { 0.0f, 1.0f, 0.0f };
}

Camera::~Camera()
{

}

void Camera::Update(float _delataT)
{
	
	m_input->UpdateMouse(&m_mouseX, &m_mouseY);
	m_cameraAngleX += m_mouseX * 0.05f;
	m_cameraAngleY -= m_mouseY * 0.05f;

	if (m_cameraAngleY > 89.0f)
	{
		m_cameraAngleY = 89.0f;
	}
	if (m_cameraAngleY < -89.0f)
	{
		m_cameraAngleY = -89.0f;
	}

	glm::vec3 front;
	front.x = cos(glm::radians(m_cameraAngleY)) * cos(glm::radians(m_cameraAngleX));
	front.y = sin(glm::radians(m_cameraAngleY));
	front.z = cos(glm::radians(m_cameraAngleY)) * sin(glm::radians(m_cameraAngleX));
	m_camFront = glm::normalize(front);

	Movement(_delataT);

	m_viewMatrix = glm::lookAt(m_camPos, m_camPos + m_camFront, m_camUp);
}

void Camera::Movement(float _delataT)
{
	float camSpeed = 2.5f * _delataT;
	if (m_input->IsKeyDown(SDL_SCANCODE_W))
	{
		m_camPos += camSpeed * m_camFront;
	}
	if (m_input->IsKeyDown(SDL_SCANCODE_S))
	{
		m_camPos -= camSpeed * m_camFront;
	}
	if (m_input->IsKeyDown(SDL_SCANCODE_A))
	{
		m_camPos -= glm::normalize(glm::cross(m_camFront, m_camUp)) * camSpeed;
	}
	if (m_input->IsKeyDown(SDL_SCANCODE_D))
	{
		m_camPos += glm::normalize(glm::cross(m_camFront, m_camUp)) * camSpeed;
	}
	if (m_input->IsKeyDown(SDL_SCANCODE_Q))
	{
		m_camPos += camSpeed * m_camUp;
	}
	if (m_input->IsKeyDown(SDL_SCANCODE_E))
	{
		m_camPos -= camSpeed * m_camUp;
	}
}