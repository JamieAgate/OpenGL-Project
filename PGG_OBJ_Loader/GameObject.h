#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include <iostream>

#include "Mesh.h"
#include "Material.h"
#include "Camera.h"

// The GameObject contains a mesh, a material and position / orientation information
class GameObject
{
public:

	GameObject(char* _objFile, char* _vertShader, char* _fragShader, char* _texture,char* _specMap, glm::vec3 _lightPos, glm::vec3 _scale, glm::vec3 _pos, Camera* _cam);
	GameObject(char* _vertShader, char* _fragShader, char* _obj,Camera* _cam);
	~GameObject();

	void SetMesh(Mesh *input) {_mesh = input;}
	void SetMaterial(Material *input) {_material = input;}
	void SetPosition( float posX, float posY, float posZ ) {m_position.x = posX; m_position.y = posY; m_position.z = posZ;}
	void SetRotation( float rotX, float rotY, float rotZ ) {_rotation.x = rotX; _rotation.y = rotY; _rotation.z = rotZ;}
	void SetScale(float _x, float _y, float _z) { m_scale.x = _x; m_scale.y = _y; m_scale.z = _z; }
	void MoveX(float _x) { m_position.x += _x; }
	void MoveY(float _y) { m_position.y += _y; }
	void MoveZ(float _z) { m_position.z += _z; }

	void SetLightPosVector(glm::vec3 _l[]) { _material->SetLightPosition(_l); }
	void SetCamFront(glm::vec3 _c) { _material->SetCamFront(_c); }

	glm::vec3 GetPos() { return m_position; }
	glm::vec3 GetCamPos() { return cam->GetCamPos(); }
	glm::vec3 GetCamFront() { return cam->GetCamFront(); }

	// Game object is current hard-coded to rotate
	virtual void Update( float deltaTs );

	// Need to give it the camera's orientation and projection
	virtual void Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix);

protected:
	Camera* cam;
	// The actual model geometry
	Mesh *_mesh;
	// The material contains the shader
	Material *_material;
	glm::vec3 m_scale;
	// Matrix for the position and orientation of the game object
	glm::mat4 _modelMatrix;
	glm::mat4 _invModelMatrix;
	
	// Position of the model
	// The model matrix must be built from this and the _rotation
	glm::vec3 m_position;
	
	// Orientation of the model
	// The model matrix must be built from this and the m_position
	glm::vec3 _rotation;


};



#endif
