
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
	m_cam = new Camera(glm::vec3(0.0f, 3.0f, 3.5f),input);
	m_lightManager = new LightManager(input);

	m_lightManager->AddLight("sphere.obj", "VertShader.txt", "LampFragShader.txt", "Image1.bmp", pointLightPositions[0], glm::vec3{ 1.0f,1.0f,1.0f });
	m_lightManager->AddLight("sphere.obj", "VertShader.txt", "LampFragShader.txt", "Image1.bmp", pointLightPositions[1], glm::vec3{ 1.0f,1.0f,1.0f });
	m_lightManager->AddLight("sphere.obj", "VertShader.txt", "LampFragShader.txt", "Image1.bmp", pointLightPositions[2], glm::vec3{ 1.0f,1.0f,1.0f });
	m_lightManager->AddLight("sphere.obj", "VertShader.txt", "LampFragShader.txt", "Image1.bmp", pointLightPositions[3], glm::vec3{ 1.0f,1.0f,1.0f });

	m_lightManager->LoadLightPositions();

	GameObject* chair = new GameObject("Chair.obj", "VertShader.txt", "FragShader.txt", "leather.bmp","leather.bmp" ,_lightPosition, glm::vec3{ 0.01f,0.01f,0.01f }, glm::vec3{0.0f,0.0f,-10.2f},m_cam);
	chair->SetRotation(0.0f, glm::radians(10.0f), 0.0f);
	GameObject* ground = new GameObject("Ground.obj", "VertShader.txt", "FragShader.txt", "grass.bmp", "grass.bmp", _lightPosition, glm::vec3{ 0.1f,0.1f,0.1f }, glm::vec3{ 0.0f,-1.05f,0.0f }, m_cam);
	GameObject* box = new GameObject("box.obj", "VertShader.txt", "FragShader.txt", "boxtex.bmp", "specMap.bmp", _lightPosition, glm::vec3{ 0.05f,0.05f,0.05f }, glm::vec3{ 2.0f,0.0f, -11.0f }, m_cam);
	Skybox* skybox = new Skybox("SkyboxVertShader.txt","SkyboxFragShader.txt","box.obj",m_cam);
	Paralax* paralaxBox = new Paralax("box.obj", "ParalaxVertShader.txt", "ParalaxFragShader.txt", "Paralax//bricks.bmp", "Paralax//bricks.bmp", _lightPosition, glm::vec3{ 0.05f,0.05f,0.05f }, glm::vec3{ 0.0f,1.0f, 0.0f }, m_cam, "Paralax//bricks_normal.bmp", "Paralax//bricks_disp.bmp");

	m_gameObjManager = new GameObjectManager(m_cam, m_lightManager);
	m_gameObjManager->AddNewGameObject("Chair", chair);
	m_gameObjManager->AddNewGameObject("Ground", ground);
	m_gameObjManager->AddNewGameObject("Box", box);
	m_gameObjManager->AddNewGameObject("Skybox", skybox);
	m_gameObjManager->AddNewGameObject("Paralax", paralaxBox);

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
	if (input->WasKeyPressed(SDL_SCANCODE_X))
	{
		ballcount++;
		m_gameObjManager->AddNewGameObject("Ball" + std::to_string(ballcount), new Ball("sphere.obj", "VertShader.txt", "FragShader.txt", "red.bmp", "red.bmp", _lightPosition, glm::vec3{ 1.0f,1.0f,1.0f }, m_cam->GetCamPos(), m_cam, input, m_cam->GetCamFront(),ballcount));
	}
}

void Scene::Draw()
{
	m_gameObjManager->Draw(_projMatrix);
}
