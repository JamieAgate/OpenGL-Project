/// \file Ball.h
/// \Code that handles the balls that can apear in the scene
/// \author Jamie Agate

#ifndef _BALL_H_
#define _BALL_H_
//File Includes
#include "GameObject.h"
#include "InputManager.h"
#include <vector>
//Header Contents
class Ball : public GameObject
{
public:
	Ball(char* _objFile, char* _vertShader, char* _fragShader, char* _texture, char* _specMap, glm::vec3 _lightPos, glm::vec3 _scale, glm::vec3 _pos, Camera* _cam, InputManager* _input, glm::vec3 _initalVelocity,int _id);//ball constructor
	~Ball();//ball destructor

	glm::vec3 GetVelocity() { return m_velocity; }//returns velocity of ball
	int GetId() { return m_id; }//retruns the balls id

	void SetVelocity(glm::vec3 _vel) { m_velocity.x = _vel.x; m_velocity.y = _vel.y; m_velocity.z = _vel.z;}//sets velocity of ball

	void CollisionCheck(); //checks collision
	void AddCollidedWithId(int _id) { m_ballsCollidedWithIds.push_back(_id);}//adds an id for what ball its collided with so it doesnt collide with the same ball on 1 frame
	void ClearCollidedWithVec() { m_ballsCollidedWithIds.clear(); }//clears the id vector
	bool CheckIfAllreadyColided(int _id);//checks of a ball has already been colided with this frame

	void Update(float deltaTs);//update

private:
	InputManager* m_input;//input manager
	int m_id;//ball id
	std::vector<int> m_ballsCollidedWithIds;//colided with ids
	const glm::vec3 m_gravity = { 0.0f,-0.0098,0.0f };//gravity
	glm::vec3 m_velocity;//velocity
};

#endif