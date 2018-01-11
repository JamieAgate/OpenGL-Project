/// \file Search.h
/// \The main scene loop that will run all update functions
/// \author Jamie Agate

#ifndef _SCENE_H_
#define _SCENE_H_
//File Includes
#include "GameObject.h"
#include "InputManager.h"
#include "Camera.h"
#include "GameObjectManager.h"
#include "Light.h"
#include "LightManager.h"
#include "Skybox.h"
#include "Ball.h"
#include "Paralax.h"

#include <GLM/glm.hpp> // This is the main GLM header
#include <GLM/gtc/matrix_transform.hpp> // This one lets us use matrix transformations
#include <GLM/gtc/type_ptr.hpp> // This one gives us access to a utility function which makes sending data to OpenGL nice and easy
#include <iostream>
#include <SDL/SDL.h>

#include <string>
//Header Contents
class Scene
{
public:
	Scene();//sceneconstructor
	~Scene();//scene destructor

	void Update( float deltaTs );//update function

	void Draw();//draw function
protected:
	InputManager* m_input;//input manager
	GameObjectManager* m_gameObjManager;//game object manager
	LightManager* m_lightManager;//light manager

	Camera* m_cam;//camera
	int m_ballcount;//number of balls in exisitance
	glm::mat4 m_projMatrix;//projection matrix
	glm::vec3 m_lightPosition;//light position
};

#endif _SCENE_H_