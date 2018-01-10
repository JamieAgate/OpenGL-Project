#ifndef _BALL_H_
#define _BALL_H_
#include "GameObject.h"
#include "InputManager.h"
#include <vector>

class Ball : public GameObject
{
public:
	Ball(char* _objFile, char* _vertShader, char* _fragShader, char* _texture, char* _specMap, glm::vec3 _lightPos, glm::vec3 _scale, glm::vec3 _pos, Camera* _cam, InputManager* _input, glm::vec3 _initalVelocity,int _id);
	~Ball();

	glm::vec3 GetVelocity() { return m_velocity; }
	int GetId() { return id; }

	void SetVelocity(glm::vec3 _vel) { m_velocity.x = _vel.x; m_velocity.y = _vel.y; m_velocity.z = _vel.z;}

	void CollisionCheck(); 
	void AddCollidedWithId(int _id) { ballsCollidedWithIds.push_back(_id);}
	void ClearCollidedWithVec() { ballsCollidedWithIds.clear(); }
	bool CheckIfAllreadyColided(int _id);

	void Update(float deltaTs);

private:
	InputManager* m_input;
	int id;
	std::vector<int> ballsCollidedWithIds;
	const glm::vec3 m_gravity = { 0.0f,-0.0098,0.0f };
	glm::vec3 m_velocity;
};

#endif