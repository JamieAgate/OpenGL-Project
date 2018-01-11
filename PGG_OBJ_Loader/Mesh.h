/// \file Mesh.h
/// \Code that creates and stores the VAO and allows model loading
/// \author Jamie Agate

#ifndef __MESH__
#define __MESH__
//File Includes
#include <GLM/glm.hpp>
#include <SDL/SDL.h>
#include "glew.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

//Header Contents
// For loading a mesh from OBJ file and keeping a reference for it
class Mesh
{
public:

	Mesh();//mesh constructor
	~Mesh();//mesh destructor
	
	// OBJ file must be triangulated
	void LoadOBJ( std::string filename, bool _paralax );
	void CreateMesh(float verticies[]);

	// Draws the mesh - must have shaders applied for this to display!
	void Draw();

protected:
	
	// OpenGL Vertex Array Object
	GLuint m_VAO;

	// Number of vertices in the mesh
	unsigned int m_numVertices;

};

#endif
