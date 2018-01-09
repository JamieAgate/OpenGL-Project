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
	m_velocity += m_gravity;
	CollisionCheck();
	if (m_input->WasLMBPressed())
	{
		m_velocity.x += cam->GetCamFront().x / 75;
		m_velocity.y += cam->GetCamFront().y / 75;
		m_velocity.z += cam->GetCamFront().z / 75;
	}
	m_position += m_velocity;
}

void Ball::CollisionCheck()
{
	if (m_position.y <= 0.1f)
	{
		m_velocity.y *= -0.95f;
	}
	if (m_position.x <= -13 || m_position.x >= 13)
	{
		m_velocity.x *= -0.95f;
	}
	if (m_position.z <= -9 || m_position.z >= 7)
	{
		m_velocity.z *= -0.95f;
	}
}

bool Ball::CheckIfAllreadyColided(int _id)
{
	if (!(std::find(ballsCollidedWithIds.begin(), ballsCollidedWithIds.end(), _id)!= ballsCollidedWithIds.end()))
	{
		return true;
	}
	else
	{
		return false;
	}
}
