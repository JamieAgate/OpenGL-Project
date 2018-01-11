/// \file Material.h
/// \Code that deals with all shaders, textures and materials
/// \author Jamie Agate

#ifndef __MATERIAL__
#define __MATERIAL__
//File Includes
#include <string>
#include <GLM/glm.hpp>
#include "glew.h"
#include <iostream>
#include <fstream>
#include <SDL/SDL.h>
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtc/matrix_transform.hpp>

//Header Contents
// Encapsulates shaders and textures
class Material
{
public:
	Material();
	~Material();

	// Loads shaders from file
	// Returns false if there was an error - it will also print out messages to console
	bool LoadShaders( std::string vertFilename, std::string fragFilename );

	// For setting the standard matrices needed by the shader
	void SetMatrices(glm::mat4 modelMatrix, glm::mat4 invModelMatrix, glm::mat4 viewMatrix, glm::mat4 projMatrix);
	
	int GetShaderProgram() { return m_shaderProgram; }//returns the shader program

	// For setting material properties
	void SetEmissiveColour( glm::vec3 input ) { m_emissiveColour = input;}
	void SetDiffuseColour( glm::vec3 input ) { m_diffuseColour = input;}
	void SetSpecularColour( glm::vec3 input ) { m_specularColour = input;}

	// Set light position in world space
	void SetLightPosition( glm::vec3 input[] ) { m_lightPosition[0] = input[0]; m_lightPosition[1] = input[1];
	m_lightPosition[2] = input[2];
	m_lightPosition[3] = input[3];
	}
	void SetCameraPos(glm::vec3 _v) { m_cameraPos = _v; }
	void SetCamFront(glm::vec3 _v) { m_camFront = _v; }

	// Sets texture
	// This applies to ambient, diffuse and specular colours
	// If you want textures for anything else, you'll need to do that yourself ;)
	bool SetTexture( std::string filename ) {m_texture1 = LoadTexture(filename); return m_texture1>0;}
	bool SetSpecular(std::string _file) { m_specularMap = LoadTexture(_file); return m_specularMap > 0; }
	bool ChangeTexture(unsigned int _tex) { m_skyboxTex = _tex; return m_texture1 > 0; }

	void setBool(const std::string &name, bool value) const;  //sets a boolen uniform in the shader
    void setInt(const std::string &name, int value) const;   //sets an int uniform in the shader
    void setFloat(const std::string &name, float value) const;//sets a float uniform in the shader
	void setVec3(const std::string &name, float x, float y, float z) const;//sets a vec3 uniform in the shader
	// Sets the material, applying the shaders
	void Apply();//applies shader to the material

protected:

	// Utility function
	bool CheckShaderCompiled( GLint shader );
	
	// The OpenGL shader program handle
	int m_shaderProgram;

	// Locations of Uniforms in the vertex shader
	int m_shaderModelMatLocation;
	int m_shaderInvModelMatLocation;
	int m_shaderViewMatLocation;
	int m_shaderProjMatLocation;

	// Location of Uniforms in the fragment shader
	int m_shaderDiffuseColLocation, m_shaderEmissiveColLocation, m_shaderSpecularColLocation;
	int m_shaderWSLightPosLocation;
	int m_shaderTex1SamplerLocation;
	int m_shaderSpecularLocation;
	int m_shaderCubeMapLocation;

	// Local store of material properties to be sent to the shader
	glm::vec3 m_emissiveColour, m_diffuseColour, m_specularColour;
	glm::vec3 m_lightPosition[4], m_cameraPos, m_camFront;

	// Loads a .bmp from file
	unsigned int LoadTexture( std::string filename );
	
	// OpenGL handle for the texture
	unsigned int m_texture1;//diffuse texture
	unsigned int m_skyboxTex;//skybox texture
	unsigned int m_specularMap;//specular map

};

#endif
