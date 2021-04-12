//Library Includes
#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include "ShaderLoader.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void InitialSetup();
void Update();
void Render();
void vboGenerate(GLuint& vbo);
void vaoGenerate(GLuint& vao);
void eboGenerate(GLuint& ebo);
void ImageGen(GLuint& image);

GLuint VBO_Tri;
GLuint VAO_Tri;
GLuint EBO_Tri;
GLuint Rayman;
GLuint Happy;

GLFWwindow* window = nullptr;

int magic = 800;
int Program_FixedTri;
int Program_PositionOnly;

float CurrentTime = 0.0f;

GLfloat Vertices_Tri[] =
{
	 0.0f, 0.0f, 0.0f,		1.0f, 0.0f, 0.0f,
	-0.5f, 0.8f, 0.0f,		0.0f, 1.0f, 0.0f,
	 0.5f, 0.8f, 0.0f,		0.0f, 0.0f, 1.0f,
};

GLfloat Vertices_Quad[] =
{
	-0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 1.0f,		//Top Left
	-0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,		//Bottom Left
	 0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 1.0f,	1.0f, 0.0f,		//Bottom Right
	 0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 1.0f,	1.0f, 1.0f,		//Top Right
};

//glm::vec3 ObjPosition = glm::vec3(0.5f, 0.5f, 0.0f);
//glm::mat4 TranslationMat;

//float ObjRotationAngle = 0.0f;
//glm::mat4 RotationMat;

//glm::vec3 ObjScale = glm::vec3(1.0f, 1.0f, 1.0f);
//glm::mat4 ScaleMat;

//glm::mat4 ObjModelMat;

//camera Stuff
//glm::vec3 CameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
//glm::vec3 CameraLookDir = glm::vec3(0.0f, 0.0f, -1.0f);
//glm::vec3 CameraTargetPos = glm::vec3(0.0f, 0.0f, 0.0f);
//glm::vec3 CameraUpDir = glm::vec3(0.0f, 1.0f, 0.0f);
//glm::mat4 ViewMat;
//glm::mat4 ProjectionMat;

//glm::vec3 ObjPosition = glm::vec3(0.0f, -100.0f, 0.0f);
//float ObjRotationAngle = 0.0f;
//glm::vec3 ObjScale = glm::vec3(400.0f, 400.0f, 1.0f);

glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 camLookDir = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camUpDir = glm::vec3(0.0f, 1.0f, 0.0f);

GLfloat Vertices_Hex[] =
{
	-0.25f, -0.5f, 0.0f,		1.0f, 0.0f, 1.0f,		0.0f, 0.0f,		//Bottom left
	 0.25f, -0.5f, 0.0f,		0.0f, 1.0f, 1.0f,		1.0f, 0.0f,		//bottom Right
	 0.5f,	 0.0f, 0.0f,		0.0f, 1.0f, 1.0f,		0.0f, 0.0f,		//middle Right
	 0.25f,  0.5f, 0.0f,		0.0f, 1.0f, 1.0f,		1.0f, 1.0f,		//top Right
	-0.25f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,		0.0f, 1.0f,		//Top Left
	-0.5f,   0.0f, 0.0f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f,		//Middle Left

};

GLfloat RainbowSquare[] =
{
	-0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,
	 0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 1.0f,
	 0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 1.0f,
};

GLuint Indices_Quad[] =
{
	0, 1, 2,
	0, 2, 3,
};

GLuint Indices_Hex[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 3, 4,
	0, 4, 5,
};

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	window = glfwCreateWindow(magic, magic, "First OpenGL window", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "GLFW failed to initialise properly. Terminating program." << std::endl;
		system("pause");

		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW failed to initialise properly. Terminating program." << std::endl;
		system("pause");

		glfwTerminate();
		return -1;
	}

	InitialSetup();

	while (glfwWindowShouldClose(window) == false)
	{
		Update();

		Render();
	}

	glfwTerminate();
	return(0);
}
void InitialSetup()
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	glViewport(0, 0, magic, magic);

	//Program_FixedTri = ShaderLoader::CreateProgram("Resources/Shaders/FixedTriangle.vs",
	//												"Resources/Shaders/FixedColor.fs");

	Program_PositionOnly = ShaderLoader::CreateProgram("Resources/Shaders/ClipSpace.vs",
		"Resources/Shaders/FixedColor.fs");

	int ImageWidth;
	int ImageHeight;
	int ImageComponents;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* ImageData = stbi_load("Resources/Textures/Rayman.jpg",
		&ImageWidth, &ImageHeight, &ImageComponents, 0);
	ImageGen(Rayman);
	
	GLint LoadedComponents = (ImageComponents == 4) ? GL_RGBA : GL_RGB;
	
	glTexImage2D(GL_TEXTURE_2D, 0, LoadedComponents, ImageWidth, ImageHeight, 0,
		LoadedComponents, GL_UNSIGNED_BYTE, ImageData);
	
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(ImageData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	int ImageWidth1;
	int ImageHeight1;
	int ImageComponents1;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* ImageData1 = stbi_load("Resources/Textures/AwesomeFace.png",
		&ImageWidth1, &ImageHeight1, &ImageComponents1, 0);
	ImageGen(Happy);
	
	GLint LoadedComponents1 = (ImageComponents1 == 4) ? GL_RGBA : GL_RGB;
	
	glTexImage2D(GL_TEXTURE_2D, 0, LoadedComponents1, ImageWidth1, ImageHeight1, 0,
		LoadedComponents1, GL_UNSIGNED_BYTE, ImageData1);
	
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(ImageData1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	float halfWindowWidth = float(magic) * 0.5f;
	float halfWindowHeight = float(magic) * 0.5f;
	//ProjectionMat = glm::ortho(-halfWindowWidth, halfWindowWidth, -halfWindowHeight, halfWindowHeight, 0.1f, 100.0f);


	vaoGenerate(VAO_Tri);
	eboGenerate(EBO_Tri);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices_Quad), Indices_Quad, GL_STATIC_DRAW);
	vboGenerate(VBO_Tri);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices_Quad), Vertices_Quad, GL_STATIC_DRAW);
	
	//glBufferData(GL_ARRAY_BUFFER, sizeof(RainbowSquare), RainbowSquare, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)0);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(9 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(3);
	//glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(12 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(4);
}
void Update()
{
	glfwPollEvents();

	CurrentTime = (float)glfwGetTime();
   
	//TranslationMat = glm::translate(glm::mat4(), ObjPosition);
	//RotationMat = glm::rotate(glm::mat4(), glm::radians(ObjRotationAngle), glm::vec3(0.0f, 0.0f, 1.0f));
	//ScaleMat = glm::scale(glm::mat4(), ObjScale);
	
	//ObjModelMat = TranslationMat * RotationMat * ScaleMat;
		// Translation Matrix
	glm::vec3 objPosition = glm::vec3(0.5f, 0.5f, 0.0f);
	glm::mat4 translationMatrix = glm::translate(glm::mat4(), objPosition);

	// Rotation Matrix
	glm::vec3 rotationAxisZ = glm::vec3(0.0f, 0.0f, 1.0f);
	float rotationAngle = 45;
	glm::mat4 rotationZ = glm::rotate(glm::mat4(), glm::radians(rotationAngle), rotationAxisZ);

	// Scale Matrix
	glm::vec3 objScale = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(), objScale);

	// Create model matrix to combine them
	glm::mat4 model = translationMatrix * rotationZ * scaleMatrix;
	GLuint modelLoc = glGetUniformLocation(Program_PositionOnly, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

	// View Matrix
	glm::mat4 view = lookAt(camPos, camPos + camLookDir, camUpDir);

	GLuint viewLoc = glGetUniformLocation(Program_PositionOnly, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));

	//// Perspective Matrix/Camera
	//glm::mat4 proj;
	//proj = glm::perspective(45.0f, (float)magic / (float)magic, 0.1f, 100.0f);
	//GLuint projLoc = glGetUniformLocation(Program_PositionOnly, "proj");
	//glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(proj));

	//// Orthographic Top Left
	//glm::mat4 proj;
	//proj = glm::ortho(0.0f, (float)magic, (float)magic, 0.0f, 0.1f, 100.0f);
	//GLuint projLoc = glGetUniformLocation(Program_PositionOnly, "proj");
	//glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(proj));

	// Orthographic Center Camera
	glm::mat4 proj;
	float halfScreenWidth = (float)magic * 0.5f;
	float halfScreenHeight = (float)magic * 0.5f;
	proj = glm::ortho(-halfScreenWidth, halfScreenWidth, -halfScreenHeight, halfScreenHeight, 0.1f, 100.0f);
	GLuint projLoc = glGetUniformLocation(Program_PositionOnly, "proj");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(proj));
	
}
void Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(Program_PositionOnly);
	glBindVertexArray(VAO_Tri);

	GLint CurrentTimeLoc = glGetUniformLocation(Program_PositionOnly, "CurrentTime");
	glUniform1f(CurrentTimeLoc, CurrentTime);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Rayman);
	glUniform1i(glGetUniformLocation(Program_PositionOnly, "ImageTexture"), 0);
	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, Happy);
	glUniform1i(glGetUniformLocation(Program_PositionOnly, "ImageTexture1"), 1);

	//GLint TranslationMatLoc = glGetUniformLocation(Program_PositionOnly, "TranslationMat");
	//glUniformMatrix4fv(TranslationMatLoc, 1, GL_FALSE, glm::value_ptr(TranslationMat));
	//
	//GLint RotationMatLoc = glGetUniformLocation(Program_PositionOnly, "RotationMat");
	//glUniformMatrix4fv(RotationMatLoc, 1, GL_FALSE, glm::value_ptr(RotationMat));
	//
	//GLint ScaleMatLoc = glGetUniformLocation(Program_PositionOnly, "ScaleMat");
	//glUniformMatrix4fv(ScaleMatLoc, 1, GL_FALSE, glm::value_ptr(ScaleMat));
	//
	//GLint TransformMatLoc = glGetUniformLocation(Program_PositionOnly, "ObjModelMat");
	//glUniformMatrix4fv(TransformMatLoc, 1, GL_FALSE, glm::value_ptr(ObjModelMat));
	
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 8, GL_UNSIGNED_INT, 0);
	//glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);

	glfwSwapBuffers(window);
}

void vaoGenerate(GLuint& vao)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
};
void vboGenerate(GLuint& vbo) {
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
};
void eboGenerate(GLuint& ebo)
{
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
};
void ImageGen(GLuint& image)
{
	glGenTextures(1, &image);
	glBindTexture(GL_TEXTURE_2D, image);
};