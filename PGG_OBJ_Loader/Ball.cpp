///  @file Ball.cpp
///  @brief Code that handles the balls that can apear in the scene

#include "Ball.h"

Ball::Ball(char* _objFile, char* _vertShader, char* _fragShader, char* _texture, char* _specMap, glm::vec3 _lightPos, glm::vec3 _scale, glm::vec3 _pos, Camera* _cam,InputManager* _input, glm::vec3 _initalVelocity, int _id) :
	GameObject(_objFile,_vertShader,_fragShader,  _texture, _specMap, _lightPos, _scale, _pos, _cam)
{
	//sets the initial velocity
	m_velocity.x = _initalVelocity.x/10;
	m_velocity.y = _initalVelocity.y/10;
	m_velocity.z = _initalVelocity.z/10;
	m_input = _input;//sets input manager
	m_id = _id;//sets the id
}


Ball::~Ball()
{

}

void Ball::Update(float deltaTs)
{
	m_material->SetCameraPos(m_cam->GetCamPos());//sets view position
	m_material->SetCamFront(m_cam->GetCamFront());//sets view direction
	m_velocity += m_gravity;//add gravity to velocity

	if (m_input->WasLMBPressed())//if lmb is pressed
	{
		//force the balls away from the camera
		m_velocity.x += m_cam->GetCamFront().x / 50;
		m_velocity.y += m_cam->GetCamFront().y / 50;
		m_velocity.z += m_cam->GetCamFront().z / 50;
	}
	CollisionCheck();//check balls collision with stage walls
	m_position += m_velocity;//update it position
}

void Ball::CollisionCheck()
{
	//keep ball in bounding box of the stage
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
	if (!(std::find(m_ballsCollidedWithIds.begin(), m_ballsCollidedWithIds.end(), _id)!= m_ballsCollidedWithIds.end()))//if the balls id isnt in the ids vector
	{
		m_ballsCollidedWithIds.push_back(_id);//push it into the vector
		return true;//it can collide
	}
	else
	{
		return false;//it cant collide
	}
}
