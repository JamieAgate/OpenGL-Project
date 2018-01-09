#include "GameObjectManager.h"

GameObjectManager::GameObjectManager(Camera* _cam, LightManager* _lightManager)
{
	m_cam = _cam;
	m_lightManager = _lightManager;
	m_CollisionManager = new CollisionManager();
}

GameObjectManager::~GameObjectManager()
{
	for (auto const& obj : m_gameObjectVector)
	{
		delete(obj.second);
	}
	m_gameObjectVector.clear();
	delete m_CollisionManager;
}

void GameObjectManager::AddNewGameObject(std::string _name,GameObject* _object)
{
	m_gameObjectVector.insert(std::pair<std::string, GameObject*>(_name, _object));
}

void GameObjectManager::AddNewGameObject(std::string _name, Ball* _object)
{
	m_gameObjectVector.insert(std::pair<std::string, GameObject*>(_name, _object));
	if (_name.find("Ball") != std::string::npos)
	{
		m_CollisionManager->AddBallToVector(_object);
	}
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

	m_CollisionManager->CheckBallCollision();

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