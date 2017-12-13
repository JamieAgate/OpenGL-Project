
#include "Scene.h"

#include <iostream>
#include <SDL/SDL.h>



Scene::Scene()
{
	_projMatrix = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);

	_lightPosition = glm::vec3(5.0f,5.0f,5.0f);
	input = new InputManager();
	m_cam = new Camera(glm::vec3(0.0f, 0.0f, 3.5f),input);

	GameObject* chair = new GameObject("Chair.obj", "VertShader.txt", "FragShader.txt", "leather.bmp","leather.bmp" ,_lightPosition, glm::vec3{ 0.01f,0.01f,0.01f }, glm::vec3{0.0f,0.0f,0.0f},m_cam);
	Light* sphereLight = new Light("sphere.obj", "VertShader.txt", "LampFragShader.txt", "Image1.bmp", _lightPosition, glm::vec3{ 0.01f,0.01f,0.01f }, _lightPosition,input);
	GameObject* ground = new GameObject("Ground.obj", "VertShader.txt", "FragShader.txt", "red.bmp", "red.bmp", _lightPosition, glm::vec3{ 0.1f,0.1f,0.1f }, glm::vec3{ -1.0f,-1.0f,-1.0f }, m_cam);
	GameObject* box = new GameObject("box.obj", "VertShader.txt", "FragShader.txt", "boxtex.bmp", "specMap.bmp", _lightPosition, glm::vec3{ 0.05f,0.05f,0.05f }, glm::vec3{ 2.0f,2.0f, 0.01f }, m_cam);

	m_gameObjManager = new GameObjectManager(m_cam);
	m_gameObjManager->AddNewGameObject("Chair", chair);
	m_gameObjManager->AddNewGameObject("SphereLight", sphereLight);
	m_gameObjManager->AddNewGameObject("Ground", ground);
	m_gameObjManager->AddNewGameObject("Box", box);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	SDL_SetRelativeMouseMode(SDL_TRUE);
}

Scene::~Scene()
{
	delete input;
	delete m_cam;
	delete m_gameObjManager;
}

void Scene::Update( float deltaTs )
{
	input->UpdateKeyboard();
	m_gameObjManager->Update( deltaTs );
	
}

void Scene::Draw()
{
	// Draw that model, giving it the camera's position and projection
	m_gameObjManager->Draw(_projMatrix);

}



