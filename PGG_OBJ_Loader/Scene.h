
#include "GameObject.h"
#include "InputManager.h"
#include "Camera.h"
#include "GameObjectManager.h"
#include "Light.h"

#include <GLM/glm.hpp> // This is the main GLM header
#include <GLM/gtc/matrix_transform.hpp> // This one lets us use matrix transformations
#include <GLM/gtc/type_ptr.hpp> // This one gives us access to a utility function which makes sending data to OpenGL nice and easy

#include <string>

class Scene
{
public:
	Scene();
	~Scene();

	void Update( float deltaTs );

	void Draw();
protected:
	InputManager* input;
	GameObjectManager* m_gameObjManager;
	Camera* m_cam;
	glm::mat4 _projMatrix;
	glm::vec3 _lightPosition;
};
