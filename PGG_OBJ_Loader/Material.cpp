///  @file Material.cpp
///  @brief Code that deals with all shaders, textures and materials

#include "Material.h"

Material::Material()
{
	// Initialise everything here
	m_shaderModelMatLocation = 0;
	m_shaderViewMatLocation = 0;
	m_shaderProjMatLocation = 0;

	m_shaderDiffuseColLocation = 0;
	m_shaderEmissiveColLocation = 0;
	m_shaderWSLightPosLocation = 0;
	m_shaderSpecularColLocation = 0;

	m_shaderTex1SamplerLocation = 0;

	m_texture1 = 0;
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
	m_shaderProgram = glCreateProgram();

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
	glAttachShader( m_shaderProgram, vShader );

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
	glAttachShader( m_shaderProgram, fShader );

	// This makes sure the vertex and fragment shaders connect together
	glLinkProgram( m_shaderProgram );
	// Check this worked
	GLint linked;
	glGetProgramiv( m_shaderProgram, GL_LINK_STATUS, &linked );
	if ( !linked )
	{
		GLsizei len;
		glGetProgramiv( m_shaderProgram, GL_INFO_LOG_LENGTH, &len );

		GLchar* log = new GLchar[len+1];
		glGetProgramInfoLog( m_shaderProgram, len, &len, log );
		std::cerr << "ERROR: Shader linking failed: " << log << std::endl;
		delete [] log;

		return false;
	}


	// We will define matrices which we will send to the shader
	// To do this we need to retrieve the locations of the shader's matrix uniform variables
	glUseProgram( m_shaderProgram );
	m_shaderModelMatLocation = glGetUniformLocation( m_shaderProgram, "modelMat" );
	m_shaderInvModelMatLocation = glGetUniformLocation( m_shaderProgram, "invModelMat" );
	m_shaderViewMatLocation = glGetUniformLocation( m_shaderProgram, "viewMat" );
	m_shaderProjMatLocation = glGetUniformLocation( m_shaderProgram, "projMat" );
		
	m_shaderDiffuseColLocation = glGetUniformLocation( m_shaderProgram, "diffuseColour" );
	m_shaderEmissiveColLocation = glGetUniformLocation( m_shaderProgram, "emissiveColour" );
	m_shaderSpecularColLocation = glGetUniformLocation( m_shaderProgram, "specularColour" );
	m_shaderWSLightPosLocation = glGetUniformLocation( m_shaderProgram, "worldSpaceLightPos" );

	m_shaderTex1SamplerLocation = glGetUniformLocation( m_shaderProgram, "material.diffuseMap" );
	m_shaderSpecularLocation = glGetUniformLocation(m_shaderProgram, "material.specMap");
	m_shaderCubeMapLocation = glGetUniformLocation(m_shaderProgram, "skybox");

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
	glUseProgram( m_shaderProgram );
		// Send matrices and uniforms
	glUniformMatrix4fv(m_shaderModelMatLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix) );
	glUniformMatrix4fv(m_shaderInvModelMatLocation, 1, GL_TRUE, glm::value_ptr(invModelMatrix) );
	glUniformMatrix4fv(m_shaderViewMatLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix) );
	glUniformMatrix4fv(m_shaderProjMatLocation, 1, GL_FALSE, glm::value_ptr(projMatrix) );
}
	
void Material::Apply()
{
	glUseProgram(m_shaderProgram);

	glUniform3fv( m_shaderEmissiveColLocation, 1, glm::value_ptr(m_emissiveColour) );
	glUniform3fv( m_shaderDiffuseColLocation, 1, glm::value_ptr(m_diffuseColour) );
	glUniform3fv( m_shaderSpecularColLocation, 1, glm::value_ptr(m_specularColour) );
	
	glUniform3f(glGetUniformLocation(m_shaderProgram,"cameraPos"),m_cameraPos.x,m_cameraPos.y,m_cameraPos.z);
	glUniform3f(glGetUniformLocation(m_shaderProgram, "viewPos"), m_cameraPos.x, m_cameraPos.y, m_cameraPos.z);

	glUniform3f(glGetUniformLocation(m_shaderProgram, "material.ambient"), 1.0f, 0.5f, 0.31f);
	glUniform3f(glGetUniformLocation(m_shaderProgram, "material.diffuse"), 1.0f, 0.5f, 0.31f);
	glUniform3f(glGetUniformLocation(m_shaderProgram, "material.specular"), 0.5f, 0.5f, 0.5f);
	glUniform1f(glGetUniformLocation(m_shaderProgram, "material.shininess"), 32.0f);
	//sets directional light
	setVec3("dirLight.direction", 4.0f, 6.0f, 3.0f);
	setVec3("lightPos", 4.0f, 6.0f, 3.0f);
	setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
	// point light 1
	setVec3("pointLights[0].position", m_lightPosition[0].x, m_lightPosition[0].y, m_lightPosition[0].z);
	setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
	setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
	setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
	setFloat("pointLights[0].constant", 1.0f);
	setFloat("pointLights[0].linear", 0.09);
	setFloat("pointLights[0].quadratic", 0.032);
	// point light 2
	setVec3("pointLights[1].position", m_lightPosition[1].x, m_lightPosition[1].y, m_lightPosition[1].z);
	setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
	setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
	setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
	setFloat("pointLights[1].constant", 1.0f);
	setFloat("pointLights[1].linear", 0.09);
	setFloat("pointLights[1].quadratic", 0.032);
	// point light 3
	setVec3("pointLights[2].position", m_lightPosition[2].x, m_lightPosition[2].y, m_lightPosition[2].z);
	setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
	setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
	setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
	setFloat("pointLights[2].constant", 1.0f);
	setFloat("pointLights[2].linear", 0.09);
	setFloat("pointLights[2].quadratic", 0.032);
	// point light 4
	setVec3("pointLights[3].position", m_lightPosition[3].x, m_lightPosition[3].y, m_lightPosition[3].z);
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
	glUniform1i(m_shaderTex1SamplerLocation,0);
	glBindTexture(GL_TEXTURE_2D, m_texture1);

	glBindTexture(GL_TEXTURE_CUBE_MAP, m_skyboxTex);

	glActiveTexture(GL_TEXTURE1);
	glUniform1i(m_shaderSpecularLocation, 1);
	glBindTexture(GL_TEXTURE_2D, m_specularMap);
}

void Material::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_shaderProgram, name.c_str()), (int)value);
}
void Material::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(m_shaderProgram, name.c_str()), value);
}
void Material::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(m_shaderProgram, name.c_str()), value);
}

void Material::setVec3(const std::string &name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(m_shaderProgram, name.c_str()), x, y, z);
}