#ifndef GAMEOBJECTMANAGER_H_
#define GAMEOBJECTMANAGER_H_
#include "GameObject.h"
#include "Mesh.h"
#include "Material.h"
#include "Camera.h"
#include "LightManager.h"

#include <string>
#include <vector>
#include <map>

class GameObjectManager
{
public:
	GameObjectManager(Camera* _cam, LightManager* _lightManager);
	~GameObjectManager();

	void AddNewGameObject(std::string _name, GameObject* _object);
	void RemoveGameObject(std::string _id);

	void Update(float _deltaT);

	void Draw(glm::mat4 _projMat);
private:
	std::map<std::string, GameObject*> m_gameObjectVector;
	Camera* m_cam;
	LightManager* m_lightManager;
};
#endif // !GAMEOBJECTMANAGER_H_