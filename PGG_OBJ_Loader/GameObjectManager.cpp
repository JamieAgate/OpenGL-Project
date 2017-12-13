#include "GameObjectManager.h"

GameObjectManager::GameObjectManager(Camera* _cam, LightManager* _lightManager)
{
	m_cam = _cam;
	m_lightManager = _lightManager;
}

GameObjectManager::~GameObjectManager()
{
	for (auto const& obj : m_gameObjectVector)
	{
		delete(obj.second);
	}
	m_gameObjectVector.clear();
}

void GameObjectManager::AddNewGameObject(std::string _name,GameObject* _object)
{
	m_gameObjectVector.insert(std::pair<std::string, GameObject*>(_name, _object));
}

void GameObjectManager::RemoveGameObject(std::string _id)
{
	m_gameObjectVector.erase(_id);
}

void GameObjectManager::Update(float _deltaT)
{
	glm::vec3 arr[4];
	for (int i = 0; i < 4; i++)
	{
		arr[i] = m_lightManager->GetLightAt(i);
	}

	for (auto const& obj : m_gameObjectVector)
	{
		obj.second->Update(_deltaT);
		obj.second->SetLightPosVector(arr);
	}
	m_cam->Update(_deltaT);
}

void GameObjectManager::Draw(glm::mat4 _projMat)
{
	for (auto const& obj : m_gameObjectVector)
	{
		obj.second->Draw(m_cam->GetViewMat(),_projMat);
	}

	m_lightManager->Draw(m_cam->GetViewMat(), _projMat);
}