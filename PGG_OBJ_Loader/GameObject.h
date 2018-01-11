/// \file GameObject.h
/// \Base class for all game objects
/// \author Jamie Agate

#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__
//File Includes
#include <iostream>
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include "Mesh.h"
#include "Material.h"
#include "Camera.h"

//Header Contents
// The GameObject contains a mesh, a material and position / orientation information
class GameObject
{
public:

	GameObject(char* _objFile, char* _vertShader, char* _fragShader, char* _texture,char* _specMap, glm::vec3 _lightPos, glm::vec3 _scale, glm::vec3 _pos, Camera* _cam);//game object consturctor
	GameObject(char* _vertShader, char* _fragShader, char* _obj,Camera* _cam);//game object constructor for skybox
	~GameObject();//game object destructor

	void SetMesh(Mesh *input) {m_mesh = input;}//sets the mesh used by the game object
	void SetMaterial(Material *input) {m_material = input;}//sets the material used by the game object
	void SetPosition( float posX, float posY, float posZ ) {m_position.x = posX; m_position.y = posY; m_position.z = posZ;}//sets objects position
	void SetRotation( float rotX, float rotY, float rotZ ) {m_rotation.x = rotX; m_rotation.y = rotY; m_rotation.z = rotZ;}//sets objects rotation
	void SetScale(float _x, float _y, float _z) { m_scale.x = _x; m_scale.y = _y; m_scale.z = _z; }//sets objects scale
	void MoveX(float _x) { m_position.x += _x; }//moves object in x axis
	void MoveY(float _y) { m_position.y += _y; }//moves object in y axis
	void MoveZ(float _z) { m_position.z += _z; }//moves object in z axis

	void SetLightPosVector(glm::vec3 _l[]) { m_material->SetLightPosition(_l); }//sets the light position for multiple lights
	void SetCamFront(glm::vec3 _c) { m_material->SetCamFront(_c); }//sets the position for the cameras front

	glm::vec3 GetPos() { return m_position; }//returns objects position
	glm::vec3 GetCamPos() { return m_cam->GetCamPos(); }//returns the cameras position
	glm::vec3 GetCamFront() { return m_cam->GetCamFront(); }//returns the cameras front direction

	// Game object is current hard-coded to rotate
	virtual void Update( float deltaTs );//base game object update function

	// Need to give it the camera's orientation and projection
	virtual void Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix);//draws game objects

protected:
	Camera* m_cam;//camera used
	Mesh *m_mesh;//The actual model geometry
	Material *m_material;// The material contains the shader
	glm::vec3 m_scale;//scale of object

	// Matrix for the position and orientation of the game object
	glm::mat4 m_modelMatrix;
	glm::mat4 m_invModelMatrix;
	
	// Position of the model
	// The model matrix must be built from this and the _rotation
	glm::vec3 m_position;
	
	// Orientation of the model
	// The model matrix must be built from this and the m_position
	glm::vec3 m_rotation;
};



#endif
