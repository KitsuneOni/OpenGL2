// INCLUDES
// System
#include <iostream>
#include <vector>
#include <time.h>
// OpenGL
#include <glew.h>
#include <glfw3.h>
// Math
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

// Custom Classes
#include "Utiliy.h"
#include "Camera.h"
#include "LightManager.h"
#include "LightSphere.h"
#include "ObjectFactory.h"

#include "SkyBox.h"

#include "Sphere.h"

GLFWwindow* Window = nullptr;

// Prototype the Functions
// OPENGL FUNCTIONS
void InitialSetup();
void Update();
void Render();
// Enable Culling
void ToggleCulling(bool Toggle);
// INPUT
void KeyInput(GLFWwindow* InputWindow, int Key, int ScanCode, int Action, int Mods);
void MouseButtonInput(GLFWwindow* InputWindow, int Button, int Action, int Mods);
void MouseCursorInput(GLFWwindow* InputWindow, double xPos, double yPos);
void TextInput(GLFWwindow* InputWindow, unsigned int CodePoint);


// Maps for the Shader/Program
std::map <const char*, GLuint> ShaderLoader::shaderMap;
std::map <std::string, GLuint> ShaderLoader::programMap;

// Map for the Texture Loader
std::map <const char*, GLuint> TextureLoader::textureMap;


// Camera
Camera* camera;

// Light Manager
LightManager* Lights;

std::vector<LightSphere*> LightsSpheres;


std::vector<Sphere*> Spheres;
Sphere* sphere;
Sphere* sphere2;
Cube* cube;

SkyBox* skybox;

// Time Handling
float PreviousTimeStep = 0.0f;
float DeltaTime;
float Timer;

// Input
bool Culling = true;
bool WireFrame = false;
bool HideMouse = false;
bool isTyping = false;
bool showCursorPos = false;

// String for Text Editing
std::string TextString;

int main()
{
	// Initilazing GLFW and setting the version to 4.6 with Core Functionality available 
	glfwInit();
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	// Create a GLFW controlled Context Window
	Window = glfwCreateWindow(Utils::WindowWidth, Utils::WindowHeight, "Summative 1", NULL, NULL);
	if (Window == NULL)
	{
		std::cout << "GLFW failed to initialize properly. Terminating Program" << std::endl;
		system("pause");

		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(Window);

	// Initializing GLEW to populate the OpenGL function Pointers
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW failed to initialize properly. Terminating Program..";
		glfwTerminate();
		return -1;
	}

	// Runs Initial Setup
	InitialSetup();

	// Main Loop
	while (glfwWindowShouldClose(Window) == false)
	{
		// Update all the objects and process
		Update();
		// Render all objects
		Render();
	}

	// Ensure Correct Shutdown
	//Audio->ShutDown();
	glfwTerminate();
	return 0;
}

void InitialSetup()
{
	srand(time(NULL));

	// Set it in to fill mode.
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Set the Clear Color and Viewport Size
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glViewport(0, 0, 800, 800);
	
	glfwWindowHint(GLFW_SAMPLES, 4);
	glEnable(GL_MULTISAMPLE);
	
	// Enable Depth testing for 3D
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//// Set the Input Callbacks
	glfwSetKeyCallback(Window, KeyInput);
	//glfwSetMouseButtonCallback(Window, MouseButtonInput);
	glfwSetCursorPosCallback(Window, MouseCursorInput);

	camera = new Camera();
	camera->SetupCamera(glm::vec3(0.0f, 0.0f, 15.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), Utils::WindowWidth, Utils::WindowHeight);

	const char* SkyBoxTexture[6] = { "MountainOutpost/Right.jpg", "MountainOutpost/Left.jpg", "MountainOutpost/Up.jpg", "MountainOutpost/Down.jpg", "MountainOutpost/Back.jpg", "MountainOutpost/Front.jpg" };
	skybox = new SkyBox(camera, SkyBoxTexture);

	Lights = new LightManager();

	Lights->AddPointLight(0, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 0.1f, 1.0f, 1.0f, 0.045f, 0.0075f);
	LightsSpheres.push_back(new LightSphere(Lights->ReturnPointLight(0).Position, Lights->ReturnPointLight(0).Color, camera));

	Lights->AddPointLight(1, glm::vec3(20.0f, 2.0f, -3.0f), glm::vec3(1.0f, 0.0f, 0.0f), 0.03, 1.0f, 1.0f, 0.022f, 0.0019f);
	LightsSpheres.push_back(new LightSphere(Lights->ReturnPointLight(1).Position, Lights->ReturnPointLight(1).Color, camera));

	//Lights->AddPointLight(2, glm::vec3(-2.0f, -40.0f, -3.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.1, 1.0f, 1.0f, 0.045f, 0.0075f);
	//Lights->AddPointLight(3, glm::vec3(-20.0f, -6.0f, 10.0f), glm::vec3(1.0f, 1.0f, 0.0f), 0.1, 1.0f, 1.0f, 0.045f, 0.0075f);

	Lights->SetDirectionalLight(glm::vec3(0.0f, -1.0f, -1.0f), glm::vec3(0.3f, 0.3f, 0.3f), 0.10f, 1.0f);

	cube = ObjectFactory::CreateCube("Resources/Textures/Crate.jpg", "Resources/Shaders/3D_Normals.vs", "Resources/Shaders/3DLight_BlinnPhongReflection.fs", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(5.0f, 5.0f, 5.0f), camera, Lights, skybox);

	Spheres = ObjectFactory::CreateSpheres(camera, Lights, skybox, 10, glm::vec2(-15, 15), glm::vec2(-15, 15), glm::vec2(-15, 15));
	Spheres[0]->SetProgram("Resources/Shaders/3D_Normals.vs", "Resources/Shaders/3DLight_BlinnPhongRim.fs");

	// Enable Culling
	ToggleCulling(Culling);
}

void Update()
{
	// Poll for events
	glfwPollEvents();
	// Get Delta Time
	float CurrentTimeStep = (float)glfwGetTime();
	DeltaTime = CurrentTimeStep - PreviousTimeStep;
	PreviousTimeStep = CurrentTimeStep;
	Timer += DeltaTime;

	for (int i = 0; i < Spheres.size(); i++)
	{
		Spheres[i]->Update(DeltaTime);
	}

	//cube->Update(DeltaTime);

	camera->CameraMovement(Window);

	skybox->Update(DeltaTime);
}

void Render()
{
	// Clear the Screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < Spheres.size(); i++)
	{
		Spheres[i]->Draw();
	}

	cube->Draw();

	/*sphere->Draw();
	sphere2->Draw();*/

	skybox->Draw();

	for (LightSphere* obj : LightsSpheres)
	{
		obj->Draw();
	}


	// Swap the Buffer
	glfwSwapBuffers(Window);
}

void ToggleCulling(bool Toggle)
{
	// Set Culling information
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	
	Toggle ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
}

	// Callback Function for KeyInput
void KeyInput(GLFWwindow* InputWindow, int Key, int ScanCode, int Action, int Mods)
{

	/*
		Close the Window
		Bound to Escape
	*/
	if (Key == GLFW_KEY_ESCAPE && Action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(Window, true);
	}

	/*
		Toggle WireFrame mode
		Bound to Space
	*/
	if (Key == GLFW_KEY_SPACE && Action == GLFW_PRESS)
	{
		if (!isTyping)	// This Catch stops it occuring when typing 
		{
			WireFrame = !WireFrame;

			if (!WireFrame)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			else
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
		}
	}

	/*
		Toggle Culling.
		Bound to 1
	*/
	if (Key == GLFW_KEY_1 && Action == GLFW_PRESS)
	{
		Culling = !Culling;
		ToggleCulling(Culling);
	}

	/*
		Toggle Mouse Visiblity.
		Bound to 0
	*/
	if (Key == GLFW_KEY_TAB && Action == GLFW_PRESS)
	{
		HideMouse = !HideMouse;

		if (!HideMouse)
		{
			camera->firstMouse = true;
			glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else
		{
			//glfwSetCursorPos(Window, 0.0f, 0.0f);
			glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		if (glfwRawMouseMotionSupported())
		{
			glfwSetInputMode(Window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		}
	}

	/*
		Enable Text Typing.
		Bound to Enter
	*/
	if (Key == GLFW_KEY_ENTER && Action == GLFW_PRESS)
	{
		isTyping = !isTyping;

		isTyping ? glfwSetCharCallback(Window, TextInput) : glfwSetCharCallback(Window, 0);
		//isTyping ? //TextMessages[1]->SetColor(glm::vec3(0.0f, 0.0f, 1.0f)) : TextMessages[1]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	}

	/*
		BackSpace for Typing
		Bound to BackSpace
	*/
	if (Key == GLFW_KEY_BACKSPACE && (Action == GLFW_PRESS ||Action == GLFW_REPEAT))
	{
		// Only Allow it to occur when typing.
		if (isTyping)
		{
			if (TextString.size() > 0)
			{
				TextString.pop_back();
			}
			//TextMessages[1]->SetText(TextString);
		}
	}

	/*
		Reset the Pyramid to Quad
		Bound to R
	*/
	if (Key == GLFW_KEY_R && Action == GLFW_PRESS)
	{
		if (!isTyping)
		{
			//pyramid->SetObjPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		}
	}

	/*
		Toggle Show Cursor Positon
		Bound to X
	*/
	if (Key == GLFW_KEY_X && Action == GLFW_PRESS)
	{
		showCursorPos = !showCursorPos;
	}
}

	// Callback Function for Mouse Cursor
void MouseCursorInput(GLFWwindow* InputWindow, double xPos, double yPos)
{
	if (HideMouse)
	{
		camera->CameraMouseMovement(xPos, yPos);
	}
}

	// Callback Function for Character Input
void TextInput(GLFWwindow* InputWindow, unsigned int CodePoint)
{
	// Add the inputed character to the string and update the Text UI
	TextString.push_back((unsigned char)CodePoint);
}