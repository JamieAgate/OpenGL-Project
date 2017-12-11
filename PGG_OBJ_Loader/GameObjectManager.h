#ifndef GAMEOBJECTMANAGER_H_
#define GAMEOBJECTMANAGER_H_
#include "GameObject.h"
#include "Mesh.h"
#include "Material.h"

#include <string>
#include <vector>
#include <map>

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void AddNewGameObject(std::string _name, GameObject* _object);
	void RemoveGameObject(std::string _id);

	void Update(float _deltaT);

	void Draw(glm::mat4 _viewMat, glm::mat4 _projMat);
private:
	std::map<std::string, GameObject*> m_gameObjectVector;
};
#endif // !GAMEOBJECTMANAGER_H_