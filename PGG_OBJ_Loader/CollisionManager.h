#include <vector>
#include <cmath>

#include "Ball.h"

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void AddBallToVector(Ball* _ball) { m_ballsVector.push_back(_ball); }

	void CheckBallCollision();
	void CollideBalls(Ball* _ball1, Ball* _ball2);

private:
	std::vector<Ball*> m_ballsVector;
};

