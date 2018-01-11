///  @file GameObject.cpp
///  @brief Base class for all game objects

#include "GameObject.h"

GameObject::GameObject(char* _objFile, char* _vertShader, char* _fragShader, char* _texture,char* _specMap, glm::vec3 _lightPos, glm::vec3 _scale, glm::vec3 _pos, Camera* _cam)
{
	Material *modelMaterial = new Material();//ceates a new material
	modelMaterial->LoadShaders(_vertShader, _fragShader);//gives it the frag/vert shaders
	modelMaterial->SetDiffuseColour(glm::vec3(1.0f, 1.0f, 1.0f));//sets the diffuse colour to be white
	modelMaterial->SetTexture(_texture);//sets texture
	if (_specMap != "")//if it has a specular map
	{
		modelMaterial->SetSpecular(_specMap);//set the specualr map
	}
	bool paralax = false;
	if (_vertShader == "ParalaxVertShader.txt")//if the vertex shader is a paralax
	{
		paralax = true;
	}
	Mesh *modelMesh = new Mesh();//creates new mesh
	modelMesh->LoadOBJ(_objFile,paralax);//gives it the obj and tells it if it is using paralax

	m_material = modelMaterial;//sets the material
	m_mesh = modelMesh;//sets the mesh
	m_scale = _scale;//sets scale
	m_position = _pos;//sets position
	m_cam = _cam;//sets the camera
}

GameObject::GameObject(char* _vertShader, char* _fragShader, char* _obj, Camera* _cam)
{
	Material *modelMaterial = new Material();//creates new material
	modelMaterial->LoadShaders(_vertShader, _fragShader);//gives it the frag/vert shaders
	modelMaterial->SetDiffuseColour(glm::vec3(1.0f, 1.0f, 1.0f));//sets the diffuse colour

	Mesh *modelMesh = new Mesh();//creates a new mesh

	//skybox verticies,normals and uvs
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

	//creates mesh from verticies
	modelMesh->CreateMesh(skyboxVertices);


	m_material = modelMaterial;//sets material
	m_mesh = modelMesh;//sets mesh
	m_cam = _cam;//sets camera
	m_position = { 0.0f,0.0f,0.0f };
	m_scale = { 3.0f,3.0f,3.0f };//sets scale
}

GameObject::~GameObject()
{
	delete m_mesh;//deletes mesh
	delete m_material;//deletes material
}

void GameObject::Update( float deltaTs )
{
	if (m_cam != nullptr)
	{
		m_material->SetCameraPos(m_cam->GetCamPos());//sets the view position
		m_material->SetCamFront(m_cam->GetCamFront());//sets the view direction
	}
}



void GameObject::Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix)
{
	if( m_mesh != NULL )
	{
		if( m_material != NULL )
		{
			
			// Make sure matrices are up to date (if you don't change them elsewhere, you can put this in the update function)
			glm::mat4 transformMat = glm::translate(glm::mat4(1.0f), m_position );
			glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), m_scale);
			glm::mat4 rotationMat = glm::rotate(glm::mat4(1.0f), m_rotation.x,glm::vec3(1.0f,0.0f,0.0f));
			rotationMat = glm::rotate(rotationMat, m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
			rotationMat = glm::rotate(rotationMat, m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
			m_modelMatrix = transformMat * scaleMat * rotationMat;

			m_material->SetMatrices(m_modelMatrix, m_invModelMatrix, viewMatrix, projMatrix);
			// This activates the shader
			m_material->Apply();
		}

		// Sends the mesh data down the pipeline
		m_mesh->Draw();

	}
}
