// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// 
// (c) 2021 Media Design School
//
// File Name   : Mesh.h
// Description : A base class that each renderable object inherets from.
//				 This stores the VAO/VBO/EBO, The Program and the camera.
// Author      : Neel Kolhe
// Mail        : Neel.Kolhe@mds.ac.nz


#pragma once
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>

#include "Camera.h"
#include "ShaderLoader.h"

class Mesh
{
public:
	// Virtual Function to Render the object. Gets overloaded when inherited.
	virtual void Draw() = 0;
	// Virtual Function to Update the object. Gets overloaded when inherited.
	virtual void Update(float DeltaTime) = 0;

	// Sets the Program to render with
	virtual void SetProgram(const char* vertexShader, const char* fragmentShader);
	// Stores a pointer to the camera
	virtual void SetCamera(Camera* newCamera);
protected:
	// VAO
	GLuint mVAO = NULL;
	// VBO
	GLuint mVBO = NULL;
	// EBO
	GLuint mEBO = NULL;
	// The Shader Program
	GLuint m_Program;
	// Pointer to the Camera
	Camera* camera;
	float m_CurrentTime;
};

