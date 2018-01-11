///  @file Scene.cpp
///  @brief The main scene loop that will run all update functions

#include "Scene.h"

Scene::Scene()
{
	m_projMatrix = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);//creates default proj matrix

	m_lightPosition = glm::vec3(5.0f,10.0f,5.0f);//sets the directional ligth postion

	//locations of all point lights
	glm::vec3 pointLightPositions[] = {
		glm::vec3(5.0f,  5.0f,  5.0f),
		glm::vec3(-5.0f, 5.0f, -5.0f),
		glm::vec3(-5.0f,  5.0f, 5.0f),
		glm::vec3(5.0f,  5.0f, -5.0f)
	};

	m_input = new InputManager();//creates the input manager
	m_cam = new Camera(glm::vec3(0.0f, 3.0f, 0.0f),m_input);//creates the camera
	m_lightManager = new LightManager(m_input);//creates the light manager

	//creates all point lights
	m_lightManager->AddLight("sphere.obj", "VertShader.txt", "LampFragShader.txt", "Image1.bmp", pointLightPositions[0], glm::vec3{ 1.0f,1.0f,1.0f });
	m_lightManager->AddLight("sphere.obj", "VertShader.txt", "LampFragShader.txt", "Image1.bmp", pointLightPositions[1], glm::vec3{ 1.0f,1.0f,1.0f });
	m_lightManager->AddLight("sphere.obj", "VertShader.txt", "LampFragShader.txt", "Image1.bmp", pointLightPositions[2], glm::vec3{ 1.0f,1.0f,1.0f });
	m_lightManager->AddLight("sphere.obj", "VertShader.txt", "LampFragShader.txt", "Image1.bmp", pointLightPositions[3], glm::vec3{ 1.0f,1.0f,1.0f });
	m_lightManager->LoadLightPositions();

	//creates all game objects for the scene
	GameObject* chair = new GameObject("Chair.obj", "VertShader.txt", "FragShader.txt", "leather.bmp","leather.bmp" ,m_lightPosition, glm::vec3{ 0.01f,0.01f,0.01f }, glm::vec3{0.0f,0.0f,-10.2f},m_cam);
	chair->SetRotation(0.0f, glm::radians(10.0f), 0.0f);
	GameObject* ground = new GameObject("Ground.obj", "VertShader.txt", "FragShader.txt", "grass.bmp", "grass.bmp", m_lightPosition, glm::vec3{ 0.1f,0.1f,0.1f }, glm::vec3{ 0.0f,-1.05f,0.0f }, m_cam);
	GameObject* box = new GameObject("box.obj", "VertShader.txt", "FragShader.txt", "boxtex.bmp", "specMap.bmp", m_lightPosition, glm::vec3{ 0.05f,0.05f,0.05f }, glm::vec3{ 2.0f,0.0f, -11.0f }, m_cam);
	Skybox* skybox = new Skybox("SkyboxVertShader.txt","SkyboxFragShader.txt","box.obj",m_cam);
	Paralax* paralaxBox = new Paralax("box.obj", "ParalaxVertShader.txt", "ParalaxFragShader.txt", "Paralax//bricks.bmp", "Paralax//bricks.bmp", m_lightPosition, glm::vec3{ 0.05f,0.05f,0.05f }, glm::vec3{ 2.0f,2.0f, -11.0f }, m_cam, "Paralax//bricks_normal.bmp", "Paralax//bricks_disp.bmp");

	m_gameObjManager = new GameObjectManager(m_cam, m_lightManager);//creates game object manager
	//adds all objects to game object manager
	m_gameObjManager->AddNewGameObject("Chair", chair);
	m_gameObjManager->AddNewGameObject("Ground", ground);
	m_gameObjManager->AddNewGameObject("Box", box);
	m_gameObjManager->AddNewGameObject("Skybox", skybox);
	m_gameObjManager->AddNewGameObject("Paralax", paralaxBox);

	//enables back face culling
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	SDL_SetRelativeMouseMode(SDL_TRUE);//sets relative mouse mode so the mouse
}

Scene::~Scene()
{
	delete m_input;
	delete m_cam;
	delete m_gameObjManager;
}

void Scene::Update( float deltaTs )
{
	m_input->UpdateKeyboard();//updates keyboard
	m_gameObjManager->Update( deltaTs );//updates all game objects
	if (m_input->WasKeyPressed(SDL_SCANCODE_X))//if x is presed
	{
		//spawn a ball
		m_ballcount++;
		m_gameObjManager->AddNewGameObject("Ball" + std::to_string(m_ballcount), new Ball("sphere.obj", "VertShader.txt", "FragShader.txt", "red.bmp", "red.bmp", m_lightPosition, glm::vec3{ 1.0f,1.0f,1.0f }, m_cam->GetCamPos(), m_cam, m_input, m_cam->GetCamFront(),m_ballcount));
	}
}

void Scene::Draw()
{
	//draws all game objects
	m_gameObjManager->Draw(m_projMatrix);
}
