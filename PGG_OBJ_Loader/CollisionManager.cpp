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
	while (i < m_ballsVector.size())
	{
		Ball* currentTestedBall = m_ballsVector.at(i);
		for (int c = 0; c < m_ballsVector.size(); c++)
		{
			if (c == i)
			{
				continue;
			}
			else
			{
				Ball* collidedBall = m_ballsVector.at(c);
				float xAxisColl = currentTestedBall->GetPos().x - collidedBall->GetPos().x;
				float yAxisColl = currentTestedBall->GetPos().y - collidedBall->GetPos().y;
				float zAxisColl = currentTestedBall->GetPos().z - collidedBall->GetPos().z;

				if ((xAxisColl * xAxisColl)  +
					(yAxisColl * yAxisColl)  +
					(zAxisColl * zAxisColl)  <
					(0.2f) && currentTestedBall->CheckIfAllreadyColided(collidedBall->GetId()))
				{
						CollideBalls(currentTestedBall, collidedBall);
				}
			}
		}
		i++;
	}

	for each(Ball* _b in m_ballsVector)
	{
		_b->ClearCollidedWithVec();
	}
}

void CollisionManager::CollideBalls(Ball* _ball1, Ball* _ball2)
{
	_ball1->AddCollidedWithId(_ball2->GetId());
	_ball2->AddCollidedWithId(_ball1->GetId());

	glm::vec3 normal = _ball1->GetPos() - _ball2->GetPos();

	float ball1ReflectAngle = glm::orientedAngle(_ball1->GetVelocity(), normal, normal);
	float ball2ReflectAngle = glm::orientedAngle(_ball2->GetVelocity(), normal, normal);

	glm::vec3 reflectedBall1Vec = glm::rotate(_ball1->GetVelocity(), ball1ReflectAngle, normal);
	glm::vec3 reflectedBall2Vec = glm::rotate(_ball2->GetVelocity(), ball2ReflectAngle, normal);

	glm::vec3 tempVel = _ball1->GetVelocity();
	tempVel.x *= 0.33;
	tempVel.y *= 0.33;
	tempVel.z *= 0.33;

	glm::vec3 tempVel2 = _ball2->GetVelocity();
	tempVel2.x *= 0.33;
	tempVel2.y *= 0.33;
	tempVel2.z *= 0.33;

	_ball1->SetVelocity(reflectedBall1Vec + tempVel2);
	_ball2->SetVelocity(reflectedBall2Vec + tempVel);
}