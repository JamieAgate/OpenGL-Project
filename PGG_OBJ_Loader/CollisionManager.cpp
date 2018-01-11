///  @file CollisionManager.cpp
///  @brief Code that handles all collisions between he balls

#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::CheckBallCollision()
{

	int i = 0;
	while (i < m_ballsVector.size())//for all balls
	{
		Ball* currentTestedBall = m_ballsVector.at(i);
		for (int c = 0; c < m_ballsVector.size(); c++)//check against all other balls
		{
			if (c == i)//if its trying to check itself
			{
				continue;
			}
			else
			{
				//check if balls are intercepting and if its alleady collided this frame
				Ball* collidedBall = m_ballsVector.at(c);
				float xAxisColl = currentTestedBall->GetPos().x - collidedBall->GetPos().x;
				float yAxisColl = currentTestedBall->GetPos().y - collidedBall->GetPos().y;
				float zAxisColl = currentTestedBall->GetPos().z - collidedBall->GetPos().z;

				if ((xAxisColl * xAxisColl)  +
					(yAxisColl * yAxisColl)  +
					(zAxisColl * zAxisColl)  <
					(0.2f) && currentTestedBall->CheckIfAllreadyColided(collidedBall->GetId()))
				{
						CollideBalls(currentTestedBall, collidedBall);//make them collide
				}
			}
		}
		i++;
	}

	//clear all ids so they can collide again
	for each(Ball* _b in m_ballsVector)
	{
		_b->ClearCollidedWithVec();
	}
}

void CollisionManager::CollideBalls(Ball* _ball1, Ball* _ball2)
{
	_ball1->AddCollidedWithId(_ball2->GetId());//add collide with
	_ball2->AddCollidedWithId(_ball1->GetId());//add collided with

	glm::vec3 normal = _ball1->GetPos() - _ball2->GetPos();//calculates the normal of the 2 coliding balls

														   //calculates the angles from the normals
	float ball1ReflectAngle = glm::orientedAngle(_ball1->GetVelocity(), normal, normal);
	float ball2ReflectAngle = glm::orientedAngle(_ball2->GetVelocity(), normal, normal);

	//rotates the vectors using the angles
	glm::vec3 reflectedBall1Vec = glm::rotate(_ball1->GetVelocity(), ball1ReflectAngle*2, normal);
	glm::vec3 reflectedBall2Vec = glm::rotate(_ball2->GetVelocity(), ball2ReflectAngle*2, normal);

	//saves old velocities
	glm::vec3 tempVel = _ball1->GetVelocity();
	tempVel.x *= 0.33;
	tempVel.y *= 0.33;
	tempVel.z *= 0.33;

	glm::vec3 tempVel2 = _ball2->GetVelocity();
	tempVel2.x *= 0.33;
	tempVel2.y *= 0.33;
	tempVel2.z *= 0.33;

	//olds the other balls velocity to the reflected velocity and sets it
	_ball1->SetVelocity(reflectedBall1Vec + tempVel2);
	_ball2->SetVelocity(reflectedBall2Vec + tempVel);
}