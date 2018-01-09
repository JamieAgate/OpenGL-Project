
#include <iostream>
#include <fstream>
#include <SDL/SDL.h>
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include "Material.h"

Material::Material()
{
	// Initialise everything here
	_shaderModelMatLocation = 0;
	_shaderViewMatLocation = 0;
	_shaderProjMatLocation = 0;

	_shaderDiffuseColLocation = 0;
	_shaderEmissiveColLocation = 0;
	_shaderWSLightPosLocation = 0;
	_shaderSpecularColLocation = 0;

	_shaderTex1SamplerLocation = 0;

	_texture1 = 0;
}

Material::~Material()
{
	// Clean up everything here
}

bool Material::LoadShaders( std::string vertFilename, std::string fragFilename )
{
	// OpenGL doesn't provide any functions for loading shaders from file
	std::ifstream vertFile( vertFilename );
	char *vShaderText = NULL;

	if( vertFile.is_open() )
	{
		// Find out how many characters are in the file
		vertFile.seekg (0, vertFile.end);
		int length = (int) vertFile.tellg();
		vertFile.seekg (0, vertFile.beg);
		
		// Create our buffer
		vShaderText = new char [length + 1];

		// Transfer data from file to buffer
		vertFile.read(vShaderText,length);

		// Check it reached the end of the file
		if( !vertFile.eof() )
		{
			vertFile.close();
			std::cerr<<"WARNING: could not read vertex shader from file: "<<vertFilename<<std::endl;
			return false;
		}

		// Find out how many characters were actually read
		length = (int) vertFile.gcount();

		// Needs to be NULL-terminated
		vShaderText[length] = 0;
		
		vertFile.close();
	}
	else
	{
		std::cerr<<"WARNING: could not open vertex shader from file: "<<vertFilename<<std::endl;
		return false;
	}

	
	std::ifstream fragFile( fragFilename );
	char *fShaderText = NULL;

	if( fragFile.is_open() )
	{
		// Find out how many characters are in the file
		fragFile.seekg (0, fragFile.end);
		int length = (int) fragFile.tellg();
		fragFile.seekg (0, fragFile.beg);
		
		// Create our buffer
		fShaderText = new char [length + 1];
		
		// Transfer data from file to buffer
		fragFile.read(fShaderText,length);
		
		// Check it reached the end of the file
		if( !fragFile.eof() )
		{
			fragFile.close();
			std::cerr<<"WARNING: could not read fragment shader from file: "<<fragFilename<<std::endl;
			return false;
		}
		
		// Find out how many characters were actually read
		length = (int) fragFile.gcount();
		
		// Needs to be NULL-terminated
		fShaderText[length] = 0;
		
		fragFile.close();
	}
	else
	{
		std::cerr<<"WARNING: could not open fragment shader from file: "<<fragFilename<<std::endl;
		return false;
	}



	// The 'program' stores the shaders
	_shaderProgram = glCreateProgram();

	// Create the vertex shader
	GLuint vShader = glCreateShader( GL_VERTEX_SHADER );
	// Give GL the source for it
	glShaderSource( vShader, 1, &vShaderText, NULL );
	// Delete buffer
	delete [] vShaderText;
	// Compile the shader
	glCompileShader( vShader );
	// Check it compiled and give useful output if it didn't work!
	if( !CheckShaderCompiled( vShader ) )
	{
		std::cerr<<"ERROR: failed to compile vertex shader"<<std::endl;
		return false;
	}
	// This links the shader to the program
	glAttachShader( _shaderProgram, vShader );

	// Same for the fragment shader
	GLuint fShader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fShader, 1, &fShaderText, NULL );
	// Delete buffer
	delete [] fShaderText;
	glCompileShader( fShader );
	if( !CheckShaderCompiled( fShader ) )
	{
		std::cerr<<"ERROR: failed to compile fragment shader"<<std::endl;
		return false;
	}
	glAttachShader( _shaderProgram, fShader );

	// This makes sure the vertex and fragment shaders connect together
	glLinkProgram( _shaderProgram );
	// Check this worked
	GLint linked;
	glGetProgramiv( _shaderProgram, GL_LINK_STATUS, &linked );
	if ( !linked )
	{
		GLsizei len;
		glGetProgramiv( _shaderProgram, GL_INFO_LOG_LENGTH, &len );

		GLchar* log = new GLchar[len+1];
		glGetProgramInfoLog( _shaderProgram, len, &len, log );
		std::cerr << "ERROR: Shader linking failed: " << log << std::endl;
		delete [] log;

		return false;
	}


	// We will define matrices which we will send to the shader
	// To do this we need to retrieve the locations of the shader's matrix uniform variables
	glUseProgram( _shaderProgram );
	_shaderModelMatLocation = glGetUniformLocation( _shaderProgram, "modelMat" );
	_shaderInvModelMatLocation = glGetUniformLocation( _shaderProgram, "invModelMat" );
	_shaderViewMatLocation = glGetUniformLocation( _shaderProgram, "viewMat" );
	_shaderProjMatLocation = glGetUniformLocation( _shaderProgram, "projMat" );
		
	_shaderDiffuseColLocation = glGetUniformLocation( _shaderProgram, "diffuseColour" );
	_shaderEmissiveColLocation = glGetUniformLocation( _shaderProgram, "emissiveColour" );
	_shaderSpecularColLocation = glGetUniformLocation( _shaderProgram, "specularColour" );
	_shaderWSLightPosLocation = glGetUniformLocation( _shaderProgram, "worldSpaceLightPos" );

	_shaderTex1SamplerLocation = glGetUniformLocation( _shaderProgram, "material.diffuseMap" );
	_shaderSpecularLocation = glGetUniformLocation(_shaderProgram, "material.specMap");
	_shaderCubeMapLocation = glGetUniformLocation(_shaderProgram, "skybox");

	return true;
}

bool Material::CheckShaderCompiled( GLint shader )
{
	GLint compiled;
	glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
	if ( !compiled )
	{
		GLsizei len;
		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &len );

		// OpenGL will store an error message as a string that we can retrieve and print
		GLchar* log = new GLchar[len+1];
		glGetShaderInfoLog( shader, len, &len, log );
		std::cerr << "ERROR: Shader compilation failed: " << log << std::endl;
		delete [] log;

		return false;
	}
	return true;
}

unsigned int Material::LoadTexture( std::string filename )
{
	// Load SDL surface
	SDL_Surface *image = SDL_LoadBMP( filename.c_str() );

	if( !image ) // Check it worked
	{
		std::cerr<<"WARNING: could not load BMP image: "<<filename<<std::endl;
		return 0;
	}

	// Create OpenGL texture
	unsigned int texName = 0;
	glGenTextures(1, &texName);

	glBindTexture(GL_TEXTURE_2D, texName);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// By default, OpenGL mag filter is linear
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// By default, OpenGL min filter will use mipmaps
	// We therefore either need to tell it to use linear or generate a mipmap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	// SDL loads images in BGR order
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_BGR, GL_UNSIGNED_BYTE, image->pixels);

	//glGenerateMipmap(GL_TEXTURE_2D);

	SDL_FreeSurface(image);
	
	//glBindTexture(GL_TEXTURE_2D, 0);

	return texName;
}

void Material::SetMatrices(glm::mat4 modelMatrix, glm::mat4 invModelMatrix, glm::mat4 viewMatrix, glm::mat4 projMatrix)
{
	glUseProgram( _shaderProgram );
		// Send matrices and uniforms
	glUniformMatrix4fv(_shaderModelMatLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix) );
	glUniformMatrix4fv(_shaderInvModelMatLocation, 1, GL_TRUE, glm::value_ptr(invModelMatrix) );
	glUniformMatrix4fv(_shaderViewMatLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix) );
	glUniformMatrix4fv(_shaderProjMatLocation, 1, GL_FALSE, glm::value_ptr(projMatrix) );
}
	
void Material::Apply()
{
	glUseProgram( _shaderProgram );

	glUniform3fv( _shaderEmissiveColLocation, 1, glm::value_ptr(_emissiveColour) );
	glUniform3fv( _shaderDiffuseColLocation, 1, glm::value_ptr(_diffuseColour) );
	glUniform3fv( _shaderSpecularColLocation, 1, glm::value_ptr(_specularColour) );
	
	glUniform3f(glGetUniformLocation(_shaderProgram,"cameraPos"),m_cameraPos.x,m_cameraPos.y,m_cameraPos.z);

	glUniform3f(glGetUniformLocation(_shaderProgram, "material.ambient"), 1.0f, 0.5f, 0.31f);
	glUniform3f(glGetUniformLocation(_shaderProgram, "material.diffuse"), 1.0f, 0.5f, 0.31f);
	glUniform3f(glGetUniformLocation(_shaderProgram, "material.specular"), 0.5f, 0.5f, 0.5f);
	glUniform1f(glGetUniformLocation(_shaderProgram, "material.shininess"), 32.0f);

	//glUniform3f(glGetUniformLocation(_shaderProgram, "light.position"), m_cameraPos.x, m_cameraPos.y, m_cameraPos.z);
	//glUniform3f(glGetUniformLocation(_shaderProgram, "light.direction"), m_camFront.x, m_camFront.y, m_camFront.z);
	//glUniform1f(glGetUniformLocation(_shaderProgram, "light.cutOff"), glm::cos(glm::radians(12.5f)));
	//glUniform1f(glGetUniformLocation(_shaderProgram, "light.outerCutOff"), glm::cos(glm::radians(17.5f)));
	//glUniform3f(glGetUniformLocation(_shaderProgram, "light.ambient"), 0.2f, 0.2f, 0.2f);
	//glUniform3f(glGetUniformLocation(_shaderProgram, "light.diffuse"), 0.5f, 0.5f, 0.5f);
	//glUniform3f(glGetUniformLocation(_shaderProgram, "light.specular"), 1.0f, 1.0f, 1.0f);
	//glUniform1f(glGetUniformLocation(_shaderProgram, "light.constant"), 1.0f);
	//glUniform1f(glGetUniformLocation(_shaderProgram, "light.linear"), 0.09f);
	//glUniform1f(glGetUniformLocation(_shaderProgram, "light.quadratic"), 0.032f);

	setVec3("dirLight.direction", 4.0f, 6.0f, 3.0f);
	setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
	// point light 1
	setVec3("pointLights[0].position", _lightPosition[0].x, _lightPosition[0].y, _lightPosition[0].z);
	setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
	setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
	setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
	setFloat("pointLights[0].constant", 1.0f);
	setFloat("pointLights[0].linear", 0.09);
	setFloat("pointLights[0].quadratic", 0.032);
	// point light 2
	setVec3("pointLights[1].position", _lightPosition[1].x, _lightPosition[1].y, _lightPosition[1].z);
	setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
	setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
	setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
	setFloat("pointLights[1].constant", 1.0f);
	setFloat("pointLights[1].linear", 0.09);
	setFloat("pointLights[1].quadratic", 0.032);
	// point light 3
	setVec3("pointLights[2].position", _lightPosition[2].x, _lightPosition[2].y, _lightPosition[2].z);
	setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
	setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
	setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
	setFloat("pointLights[2].constant", 1.0f);
	setFloat("pointLights[2].linear", 0.09);
	setFloat("pointLights[2].quadratic", 0.032);
	// point light 4
	setVec3("pointLights[3].position", _lightPosition[3].x, _lightPosition[3].y, _lightPosition[3].z);
	setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
	setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
	setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
	setFloat("pointLights[3].constant", 1.0f);
	setFloat("pointLights[3].linear", 0.09);
	setFloat("pointLights[3].quadratic", 0.032);

	//spotlight
	setVec3("flashlight.position", m_cameraPos.x, m_cameraPos.y, m_cameraPos.z);
	setVec3("flashlight.direction", m_camFront.x, m_camFront.y, m_camFront.z);
	setFloat("flashlight.cutOff", glm::cos(glm::radians(12.5f)));
	setFloat("flashlight.outerCutOff", glm::cos(glm::radians(17.5f)));
	setVec3("flashlight.ambient", 0.0f, 0.0f, 0.0f);
	setVec3("flashlight.diffuse", 1.0f, 1.0f, 1.0f);
	setVec3("flashlight.specular", 1.0f, 1.0f, 1.0f);
	setFloat("flashlight.constant", 1.0f);
	setFloat("flashlight.linear", 0.09f);
	setFloat("flashlight.quadratic", 0.032f);

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(_shaderTex1SamplerLocation,0);
	glBindTexture(GL_TEXTURE_2D, _texture1);

	glBindTexture(GL_TEXTURE_CUBE_MAP, _skyboxTex);

	glActiveTexture(GL_TEXTURE1);
	glUniform1i(_shaderSpecularLocation, 1);
	glBindTexture(GL_TEXTURE_2D, m_specularMap);
}

void Material::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(_shaderProgram, name.c_str()), (int)value);
}
void Material::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(_shaderProgram, name.c_str()), value);
}
void Material::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(_shaderProgram, name.c_str()), value);
}

void Material::setVec3(const std::string &name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(_shaderProgram, name.c_str()), x, y, z);
}