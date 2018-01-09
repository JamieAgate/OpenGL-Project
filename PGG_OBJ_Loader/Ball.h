#include "GameObject.h"
#include "InputManager.h"

class Ball : public GameObject
{
public:
	Ball(char* _objFile, char* _vertShader, char* _fragShader, char* _texture, char* _specMap, glm::vec3 _lightPos, glm::vec3 _scale, glm::vec3 _pos, Camera* _cam, InputManager* _input);
	~Ball();

	void CollisionCheck(); 

	void Update(float deltaTs);

private:
	InputManager* m_input;

	const glm::vec3 m_gravity = { 0.0f,-0.0098,0.0f };
	glm::vec3 m_velocity;
};

