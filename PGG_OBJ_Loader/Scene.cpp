
#include "Scene.h"

#include <iostream>
#include <SDL/SDL.h>

Scene::Scene()
{
	_projMatrix = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);

	_lightPosition = glm::vec3(5.0f,5.0f,5.0f);

	glm::vec3 pointLightPositions[] = {
		glm::vec3(5.0f,  5.0f,  5.0f),
		glm::vec3(-5.0f, 5.0f, -5.0f),
		glm::vec3(-5.0f,  5.0f, 5.0f),
		glm::vec3(5.0f,  5.0f, -5.0f)
	};

	input = new InputManager();
	m_cam = new Camera(glm::vec3(0.0f, 0.0f, 3.5f),input);
	m_lightManager = new LightManager(input);

	m_lightManager->AddLight("sphere.obj", "VertShader.txt", "LampFragShader.txt", "Image1.bmp", pointLightPositions[0], glm::vec3{ 0.01f,0.01f,0.01f });
	m_lightManager->AddLight("sphere.obj", "VertShader.txt", "LampFragShader.txt", "Image1.bmp", pointLightPositions[1], glm::vec3{ 0.01f,0.01f,0.01f });
	m_lightManager->AddLight("sphere.obj", "VertShader.txt", "LampFragShader.txt", "Image1.bmp", pointLightPositions[2], glm::vec3{ 0.01f,0.01f,0.01f });
	m_lightManager->AddLight("sphere.obj", "VertShader.txt", "LampFragShader.txt", "Image1.bmp", pointLightPositions[3], glm::vec3{ 0.01f,0.01f,0.01f });

	m_lightManager->LoadLightPositions();

	GameObject* chair = new GameObject("Chair.obj", "VertShader.txt", "FragShader.txt", "leather.bmp","leather.bmp" ,_lightPosition, glm::vec3{ 0.01f,0.01f,0.01f }, glm::vec3{0.0f,0.0f,0.0f},m_cam);
	GameObject* ground = new GameObject("Ground.obj", "VertShader.txt", "FragShader.txt", "grass.bmp", "grass.bmp", _lightPosition, glm::vec3{ 0.1f,0.1f,0.1f }, glm::vec3{ -1.0f,-1.0f,-1.0f }, m_cam);
	GameObject* box = new GameObject("box.obj", "VertShader.txt", "FragShader.txt", "boxtex.bmp", "specMap.bmp", _lightPosition, glm::vec3{ 0.05f,0.05f,0.05f }, glm::vec3{ 2.0f,2.0f, 0.0f }, m_cam);
	Ball* ball = new Ball("sphere.obj", "VertShader.txt", "FragShader.txt", "red.bmp", "red.bmp", _lightPosition, glm::vec3{ 0.01f,0.01f,0.01f }, glm::vec3{ -2.0f,5.0f,-2.0f }, m_cam, input);
	Skybox* skybox = new Skybox("SkyboxVertShader.txt","SkyboxFragShader.txt","box.obj",m_cam);

	m_gameObjManager = new GameObjectManager(m_cam, m_lightManager);
	m_gameObjManager->AddNewGameObject("Chair", chair);
	m_gameObjManager->AddNewGameObject("Ground", ground);
	m_gameObjManager->AddNewGameObject("Box", box);
	m_gameObjManager->AddNewGameObject("Ball", ball);
	m_gameObjManager->AddNewGameObject("Skybox", skybox);

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
	m_gameObjManager->Draw(_projMatrix);
}
