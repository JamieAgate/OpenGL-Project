
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include "GameObject.h"

GameObject::GameObject(char* _objFile, char* _vertShader, char* _fragShader, char* _texture,char* _specMap, glm::vec3 _lightPos, glm::vec3 _scale, glm::vec3 _pos, Camera* _cam)
{
	Material *modelMaterial = new Material();
	modelMaterial->LoadShaders(_vertShader, _fragShader);
	modelMaterial->SetDiffuseColour(glm::vec3(1.0f, 1.0f, 1.0f));
	modelMaterial->SetTexture(_texture);
	if (_specMap != "")
	{
		modelMaterial->SetSpecular(_specMap);
	}
	bool paralax = false;
	if (_vertShader == "ParalaxVertShader.txt")
	{
		paralax = true;
	}
	Mesh *modelMesh = new Mesh();
	modelMesh->LoadOBJ(_objFile,paralax);

	_material = modelMaterial;
	_mesh = modelMesh;
	m_scale = _scale;
	m_position = _pos;
	cam = _cam;
}

GameObject::GameObject(char* _vertShader, char* _fragShader, char* _obj, Camera* _cam)
{
	Material *modelMaterial = new Material();
	modelMaterial->LoadShaders(_vertShader, _fragShader);
	modelMaterial->SetDiffuseColour(glm::vec3(1.0f, 1.0f, 1.0f));

	Mesh *modelMesh = new Mesh();

	float skyboxVertices[] = {
		// positions          
		-50.0f,  50.0f, -50.0f,
		-50.0f, -50.0f, -50.0f,
		50.0f, -50.0f, -50.0f,
		50.0f, -50.0f, -50.0f,
		50.0f,  50.0f, -50.0f,
		-50.0f,  50.0f, -50.0f,

		-50.0f, -50.0f,  50.0f,
		-50.0f, -50.0f, -50.0f,
		-50.0f,  50.0f, -50.0f,
		-50.0f,  50.0f, -50.0f,
		-50.0f,  50.0f,  50.0f,
		-50.0f, -50.0f,  50.0f,

		50.0f, -50.0f, -50.0f,
		50.0f, -50.0f,  50.0f,
		50.0f,  50.0f,  50.0f,
		50.0f,  50.0f,  50.0f,
		50.0f,  50.0f, -50.0f,
		50.0f, -50.0f, -50.0f,

		-50.0f, -50.0f,  50.0f,
		-50.0f,  50.0f,  50.0f,
		50.0f,  50.0f,  50.0f,
		50.0f,  50.0f,  50.0f,
		50.0f, -50.0f,  50.0f,
		-50.0f, -50.0f,  50.0f,

		-50.0f,  50.0f, -50.0f,
		50.0f,  50.0f, -50.0f,
		50.0f,  50.0f,  50.0f,
		50.0f,  50.0f,  50.0f,
		-50.0f,  50.0f,  50.0f,
		-50.0f,  50.0f, -50.0f,

		-50.0f, -50.0f, -50.0f,
		-50.0f, -50.0f,  50.0f,
		50.0f, -50.0f, -50.0f,
		50.0f, -50.0f, -50.0f,
		-50.0f, -50.0f,  50.0f,
		50.0f, -50.0f,  50.0f
	};

	modelMesh->CreateMesh(skyboxVertices);

	m_scale = { 3.0f,3.0f,3.0f };

	_material = modelMaterial;
	_mesh = modelMesh;
	cam = _cam;
	m_position = { 0.0f,0.0f,0.0f };
}

GameObject::~GameObject()
{
	delete _mesh;
	delete _material;
}

void GameObject::Update( float deltaTs )
{
	if (cam != nullptr)
	{
		_material->SetCameraPos(cam->GetCamPos());
		_material->SetCamFront(cam->GetCamFront());

		//std::cout << cam->GetCamFront().x << ", " << cam->GetCamFront().y << ", " << cam->GetCamFront().z << "\n";
	}
}



void GameObject::Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix)
{
	if( _mesh != NULL )
	{
		if( _material != NULL )
		{
			
			// Make sure matrices are up to date (if you don't change them elsewhere, you can put this in the update function)
			glm::mat4 transformMat = glm::translate(glm::mat4(1.0f), m_position );
			glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), m_scale);
			glm::mat4 rotationMat = glm::rotate(glm::mat4(1.0f), _rotation.x,glm::vec3(1.0f,0.0f,0.0f));
			rotationMat = glm::rotate(rotationMat, _rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
			rotationMat = glm::rotate(rotationMat, _rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
			_modelMatrix = transformMat * scaleMat * rotationMat;

			_material->SetMatrices(_modelMatrix, _invModelMatrix, viewMatrix, projMatrix);
			// This activates the shader
			_material->Apply();
		}

		// Sends the mesh data down the pipeline
		_mesh->Draw();

	}
}
