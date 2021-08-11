// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// 
// (c) 2021 Media Design School
//
// File Name   : Camera.h
// Description : A class to handle the Camera object
// Author      : Neel Kolhe
// Mail        : Neel.Kolhe@mds.ac.nz

#pragma once
#include <iostream>
// OpenGL
#include <glew.h>
#include <glfw3.h>
// Math
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

// Custom Functions
#include "Utiliy.h"

class Camera
{
public:
	// Constructor
	Camera();
	// Destructor
	~Camera();

	// Set up the Camera with all relevant information
	void SetupCamera(glm::vec3 Pos, glm::vec3 LookDir, glm::vec3 TargetPos, glm::vec3 UpDir, int windowWidth, int windowHeight);

	// Set a new Camera Position
	void setCameraPositon(glm::vec3 newPos);
	// Return the Current Camear Position
	glm::vec3 returnCameraPosition();

	// Projection, View and PVM Matricies
	// Set the Perspective Projection Matrix
	glm::mat4 PerspectiveProjectionMat(int WindowWidth, int WindowHeight);
	// Set the OrthoProjection Matrix
	glm::mat4 OrthoProjectionMat(int WindowWidth, int WindowHeight);
	// Set the View matrix
	glm::mat4 SetViewMat();
	// Return PVM Matrix. This is used in the draw function for the renderable objects.
	glm::mat4 ReturnOrthPVM();
	glm::mat4 ReturnPersPVM(glm::mat4 modelMatrix);

	void RotateAroundCentre(float Radius);

	void CameraMouseMovement(double xPos, double yPos);
	void CameraMovement(GLFWwindow* window);


	bool firstMouse = true;
private:
	// Position of the Camera
	glm::vec3 CameraPos;
	// Where the Camera is Looking
	glm::vec3 CameraLookDir;
	// The Target for the Camera
	glm::vec3 CameraTargetPos;
	// What Direction is Up for the Camera
	glm::vec3 CameraUpDir;
	// View Matrix
	glm::mat4 ViewMat;
	// Projection Matrix
	glm::mat4 OrthProjectionMat;
	glm::mat4 PersProjectionMat;

	// Window Size
	float WindowWidth;
	float WindowHeight;



	// Camera Movement::
	float MouseSensitivity = 0.5f;

	double lastX = 0.0f;
	double lastY = 0.0f;

	float yaw = -90.0f;
	float pitch = 0.0f;

	const float MINPITCH = -89.0f;
	const float MAXPITCH = 89.0f;

	float cameraSpeed = 0.05f;

	const float MAXSPEED = 2.0f;
};

