// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// 
// (c) 2021 Media Design School
//
// File Name   : ShaderLoader.h
// Description : A class to load in new Shaders. Will store the Shaders and reuse them if they get attempted to be created again. Returns a Program
// Author      : Neel Kolhe
// Mail        : Neel.Kolhe@mds.ac.nz

#pragma once

// Library Includes
#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <map>

class ShaderLoader
{
	
public:	
	// Static Function to create a new Program of Shaders
	static GLuint CreateProgram(const char* VertexShaderFilename, const char* FragmentShaderFilename);

private:
	// Constructor
	ShaderLoader(void);
	// Destructor
	~ShaderLoader(void);
	// Create a shader from the shader type and the shader name
	static GLuint CreateShader(GLenum shaderType, const char* shaderName);
	// Read the actual Shader File
	static std::string ReadShaderFile(const char *filename);
	// Return if there is an error
	static void PrintErrorDetails(bool isShader, GLuint id, const char* name);

	// A Map to handle the created shaders
	static std::map <const char*, GLuint> shaderMap;
	// A Map to handle the createad Programs
	static std::map <std::string, GLuint> programMap;
};

