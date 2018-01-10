#include "Ball.h"



Ball::Ball(char* _objFile, char* _vertShader, char* _fragShader, char* _texture, char* _specMap, glm::vec3 _lightPos, glm::vec3 _scale, glm::vec3 _pos, Camera* _cam,InputManager* _input, glm::vec3 _initalVelocity, int _id) :
	GameObject(_objFile,_vertShader,_fragShader,  _texture, _specMap, _lightPos, _scale, _pos, _cam)
{
	m_velocity.x = _initalVelocity.x/10;
	m_velocity.y = _initalVelocity.y/10;
	m_velocity.z = _initalVelocity.z/10;
	m_input = _input;
	id = _id;
}


Ball::~Ball()
{

}

void Ball::Update(float deltaTs)
{
	_material->SetCameraPos(cam->GetCamPos());
	_material->SetCamFront(cam->GetCamFront());
	m_velocity += m_gravity;
	if (m_input->WasLMBPressed())
	{
		m_velocity.x += cam->GetCamFront().x / 50;
		m_velocity.y += cam->GetCamFront().y / 50;
		m_velocity.z += cam->GetCamFront().z / 50;
	}
	CollisionCheck();
	m_position += m_velocity;
}

void Ball::CollisionCheck()
{
	if (m_position.y <= 0.1f)
	{
		m_position.y = 0.1f;
		m_velocity.y *= -0.9f;
	}
	if (m_position.x <= -14.0f || m_position.x >= 14.0f)
	{
		m_velocity.x *= -0.9f;
	}
	if (m_position.z <= -7.0f || m_position.z >= 7.0f)
	{
		m_velocity.z *= -0.9f;
	}

	if (m_velocity.x > 5.0f)
	{
		m_velocity.x = 5.0f;
	}
	if (m_velocity.x < -5.0f)
	{
		m_velocity.x = -5.0f;
	}

	if (m_velocity.z > 5.0f)
	{
		m_velocity.z = 5.0f;
	}
	if (m_velocity.z < -5.0f)
	{
		m_velocity.z = -5.0f;
	}
}

bool Ball::CheckIfAllreadyColided(int _id)
{
	if (!(std::find(ballsCollidedWithIds.begin(), ballsCollidedWithIds.end(), _id)!= ballsCollidedWithIds.end()))
	{
		ballsCollidedWithIds.push_back(_id);
		return true;
	}
	else
	{
		return false;
	}
}
