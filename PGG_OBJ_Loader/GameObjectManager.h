/// \file GameObjectManager.h
/// \Code that manages all game objects in the scene
/// \author Jamie Agate

#ifndef GAMEOBJECTMANAGER_H_
#define GAMEOBJECTMANAGER_H_
//File Includes
#include "GameObject.h"
#include "Mesh.h"
#include "Material.h"
#include "Camera.h"
#include "LightManager.h"
#include "CollisionManager.h"
#include "Ball.h"

#include <string>
#include <vector>
#include <map>
//Header Contents
class GameObjectManager
{
public:
	GameObjectManager(Camera* _cam, LightManager* _lightManager);//game object manager constructor
	~GameObjectManager();//game object manager destructor

	void AddNewGameObject(std::string _name, GameObject* _object);//adds a new game object to the vector
	void AddNewGameObject(std::string _name, Ball* _object);//adds a ball to the game obect vector
	void RemoveGameObject(std::string _id);//removes a game object

	void Update(float _deltaT);//updates all game objects

	void Draw(glm::mat4 _projMat);//draws all game objects
private:
	std::map<std::string, GameObject*> m_gameObjectVector;//map of all game objects and names
	Camera* m_cam;//camera
	LightManager* m_lightManager;//light manager
	CollisionManager* m_CollisionManager;//collision manager
};
#endif // !GAMEOBJECTMANAGER_H_