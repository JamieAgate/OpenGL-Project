/// \file CollisionManager.h
/// \Code that handles all collisions between he balls
/// \author Jamie Agate


#ifndef _COLLISIONMANAGER_H_
#define _COLLISIONMANAGER_H_
//File Includes
#include <vector>
#include <GLM\gtx\vector_angle.hpp>
#include <cmath>

#include "Ball.h"
//Header Contents
class CollisionManager
{
public:
	CollisionManager();//collision manager constructor
	~CollisionManager();//colision manager destructor

	void AddBallToVector(Ball* _ball) { m_ballsVector.push_back(_ball); }//adds a ball to the balls vector

	void CheckBallCollision();//checks the collision of all balls
	void CollideBalls(Ball* _ball1, Ball* _ball2);//collides the balls and changes their velocities

private:
	std::vector<Ball*> m_ballsVector;//balls vector
};

#endif // !_COLLISIONMANAGER_H_



