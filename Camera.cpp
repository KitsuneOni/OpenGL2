#include "Camera.h"

// Empty Default Constructor
Camera::Camera()
{
	WindowWidth = Utils::WindowWidth;
	WindowHeight = Utils::WindowHeight;
}

// Empty Default Destructor
Camera::~Camera()
{
}

// Set up the Camera with the inputed data
void Camera::SetupCamera(glm::vec3 Pos, glm::vec3 LookDir, glm::vec3 TargetPos, glm::vec3 UpDir, int windowWidth, int windowHeight)
{
	/*
		Initially stores all of the passed in information.
		Then creates the View Matrix and OrthoProjection Matrix
	*/
	CameraPos = Pos;
	CameraLookDir = LookDir;
	CameraTargetPos = TargetPos;
	CameraUpDir = UpDir;
	SetViewMat();
	OrthoProjectionMat(windowWidth, windowHeight);
	PerspectiveProjectionMat(windowWidth, windowHeight);
}

// Allows you to change the camera position at run time
void Camera::setCameraPositon(glm::vec3 newPos)
{
	CameraPos = newPos;
}

// Returns the current camera position
glm::vec3 Camera::returnCameraPosition()
{
	return(CameraPos);
}

glm::mat4 Camera::PerspectiveProjectionMat(int WindowWidth, int WindowHeight)
{
	PersProjectionMat = glm::perspective(glm::radians(45.0f), (float)WindowWidth / (float)WindowHeight, 0.1f, 4000.0f);
	return(PersProjectionMat);
}

// Sets the orthographic Projection Matrix 
glm::mat4 Camera::OrthoProjectionMat(int WindowWidth, int WindowHeight)
{
	OrthProjectionMat = glm::ortho(0.0f, (GLfloat)WindowWidth, 0.0f, (GLfloat)WindowHeight, 0.0f, 100.0f);
	return(OrthProjectionMat);
}

// Creates the View Matrix
glm::mat4 Camera::SetViewMat()
{
	ViewMat = glm::lookAt(CameraPos, CameraPos + CameraLookDir, CameraUpDir);
	return(ViewMat);
}

glm::mat4 Camera::ReturnOrthPVM()
{
	return(OrthProjectionMat);
}

// Returns the PVM Matrix with the inputted model matrix. Used for rendering
glm::mat4 Camera::ReturnPersPVM(glm::mat4 modelMatrix)
{
	return(PersProjectionMat * SetViewMat() * modelMatrix);
}

void Camera::RotateAroundCentre(float Radius)
{
	float camX = (float) cos(glfwGetTime()) * Radius;
	float camZ = (float) sin(glfwGetTime()) * Radius;

	ViewMat = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), CameraUpDir);
}

void Camera::CameraMouseMovement(double xPos, double yPos)
{
	if (glfwRawMouseMotionSupported())
	{
		if (firstMouse)
		{

			lastX = xPos;
			lastY = yPos;
			firstMouse = false;
		}

		float xOffset = (float) (xPos - lastX);
		float yOffset = (float) (lastY - yPos);
		lastX = xPos;
		lastY = yPos;

		xOffset *= MouseSensitivity;
		yOffset *= MouseSensitivity;

		yaw += xOffset;
		pitch += yOffset;

		pitch = std::fmax(MINPITCH, std::fmin(pitch, MAXPITCH));

		glm::vec3 directon;
		directon.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		directon.y = sin(glm::radians(pitch));
		directon.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

		CameraLookDir = glm::normalize(directon);
		glm::vec3 Right = glm::normalize(glm::cross(CameraLookDir, glm::vec3(0.0f, 1.0f, 0.0f)));
		CameraUpDir = glm::normalize(glm::cross(Right, CameraLookDir));
	}
}

void Camera::CameraMovement(GLFWwindow* window)
{
	float cameraAccel = 1.0f;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		cameraAccel = MAXSPEED;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		CameraPos += cameraSpeed * cameraAccel * CameraLookDir;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		CameraPos -= cameraSpeed * cameraAccel * CameraLookDir;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		CameraPos -= glm::normalize(glm::cross(CameraLookDir, CameraUpDir)) * cameraSpeed * cameraAccel;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		CameraPos += glm::normalize(glm::cross(CameraLookDir, CameraUpDir)) * cameraSpeed * cameraAccel;
	}
}

