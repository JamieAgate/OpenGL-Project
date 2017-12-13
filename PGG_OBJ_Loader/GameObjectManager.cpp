#include "GameObjectManager.h"

GameObjectManager::GameObjectManager(Camera* _cam)
{
	m_cam = _cam;
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
	for (auto const& obj : m_gameObjectVector)
	{
		obj.second->Update(_deltaT);
	}
	m_cam->Update(_deltaT);
}

void GameObjectManager::Draw(glm::mat4 _projMat)
{
	glm::vec3 light = m_gameObjectVector.at("SphereLight")->GetPos();
	for (auto const& obj : m_gameObjectVector)
	{
	/*	obj.second->SetLightPos(obj.second->GetCamPos());
		obj.second->SetCamFront(obj.second->GetCamFront());*/
		obj.second->Draw(m_cam->GetViewMat(),_projMat);
	}
}