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
					(0.1f) && currentTestedBall->CheckIfAllreadyColided(collidedBall->GetId()))
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

	glm::vec3 tempVelocity = _ball1->GetVelocity();

	_ball1->SetVelocity(_ball2->GetVelocity());
	_ball2->SetVelocity(tempVelocity);
}