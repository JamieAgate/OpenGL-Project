///  @file GameObjectManager.cpp
///  @brief Code that manages all game objects in the scene

#include "GameObjectManager.h"

GameObjectManager::GameObjectManager(Camera* _cam, LightManager* _lightManager)
{
	m_cam = _cam;//sets the camera
	m_lightManager = _lightManager;//sets the light manager
	m_CollisionManager = new CollisionManager();//creates new collision manager
}

GameObjectManager::~GameObjectManager()
{
	for (auto const& obj : m_gameObjectVector)//deletes all objects
	{
		delete(obj.second);
	}
	m_gameObjectVector.clear();
	delete m_CollisionManager;//deletes collision manager
}

void GameObjectManager::AddNewGameObject(std::string _name,GameObject* _object)
{
	m_gameObjectVector.insert(std::pair<std::string, GameObject*>(_name, _object));//adds new object to the map
}

void GameObjectManager::AddNewGameObject(std::string _name, Ball* _object)
{
	m_gameObjectVector.insert(std::pair<std::string, GameObject*>(_name, _object));//adds new ball to map
	m_CollisionManager->AddBallToVector(_object);//adds ball vector
}

void GameObjectManager::RemoveGameObject(std::string _id)
{
	m_gameObjectVector.erase(_id);//removes object from map
}

void GameObjectManager::Update(float _deltaT)
{
	//gets all point lights positions
	glm::vec3 arr[4];
	for (int i = 0; i < 4; i++)
	{
		arr[i] = m_lightManager->GetLightAt(i);
	}

	//updates all game objects
	for (auto const& obj : m_gameObjectVector)
	{
		obj.second->Update(_deltaT);//updates
		obj.second->SetLightPosVector(arr);//sets point light positions in material
	}

	m_CollisionManager->CheckBallCollision();//checks all ball collisions

	m_cam->Update(_deltaT);//updates camera


}

void GameObjectManager::Draw(glm::mat4 _projMat)
{
	for (auto const& obj : m_gameObjectVector)//draws all game objects
	{
		obj.second->Draw(m_cam->GetViewMat(),_projMat);
	}

	m_lightManager->Draw(m_cam->GetViewMat(), _projMat);//draws all point lights
}