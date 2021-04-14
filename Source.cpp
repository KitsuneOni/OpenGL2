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
void ImageClear(unsigned char* image);

GLuint VBO_Hex;
GLuint VAO_Hex;
GLuint EBO_Hex;

GLuint VAO_Quad;
GLuint VBO_Quad;
GLuint EBO_Quad;

GLuint Elige;
GLuint Mood;
GLuint AnimationSprite;

GLFWwindow* window = nullptr;

int magic = 800;
int Program_Hex;
int Program_Quad;

float CurrentTime = 0.0f;
float PreviousTimeStep;
float AnimationTimeX = 0.0f;
float AnimationTimeY = 0.0f;
float PositionSpriteX;

glm::vec3 ObjPositionRight = glm::vec3(200.0f, 200.0f, 0.0f);
glm::vec3 ObjPositionLeft = glm::vec3(-200.0f, 200.0f, 0.0f);
glm::vec3 ObjPositionQuad = glm::vec3(0.0f, -200.0f, 0.0f);

glm::mat4 TranslationMat;

float ObjRotationAngle = 0.0f;
glm::mat4 RotationMat;

glm::vec3 ObjScale = glm::vec3(200.0f, 200.0f, 200.0f);
glm::mat4 ScaleMat;

glm::mat4 ObjModelMat;
glm::mat4 PVMMatHexRight;
glm::mat4 PVMMatHexLeft;
glm::mat4 PVMMatQuad;

//camera Stuff
glm::vec3 CameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 CameraLookDir = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 CameraTargetPos = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 CameraUpDir = glm::vec3(0.0f, 1.0f, 0.0f);
glm::mat4 ViewMat;
glm::mat4 ProjectionMat;

GLfloat Vertices_Hex[] =
{
	 0.0f,   0.0f, 0.0f,		1.0f, 0.0f, 1.0f,		0.5f, 0.5f,		//Center
	-0.25f,  0.5f, 0.0f,		0.0f, 1.0f, 1.0f,		0.25f, 1.0f,	//Top Left
	 0.25f,	 0.5f, 0.0f,		0.0f, 1.0f, 1.0f,		0.75f, 1.0f,	//Top Right
	 0.5f,   0.0f, 0.0f,		0.0f, 1.0f, 1.0f,		1.0f, 0.5f,		//Middle Right
	 0.25f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,		0.75f, 0.0f,	//Bottom Right
	-0.25f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,		0.25f, 0.0f,	//Bottom Left
	-0.5f,   0.0f, 0.0f,		0.0f, 1.0f, 0.0f,		0.0f, 0.5f,		//Middle Left

};

GLuint Indices_Hex[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 3, 4,
	0, 4, 5,
	0, 5, 6,
	0, 6, 1,
};

GLfloat Vertices_Quad[] =
{
	-1.0f, -1.0f, 0.0f,    		 1.0f, 0.0f, 1.0f,		0.0f,  0.0f,		//bottom left
	 1.0f, -1.0f, 0.0f,			 0.0f, 1.0f, 1.0f,		0.125f,	0.0f,		//bottom right
     1.0f,  1.0f, 0.0f,			 0.0f, 1.0f, 1.0f,		0.125f,  1.0f,		//top right
	-1.0f,  1.0f, 0.0f,			 0.0f, 1.0f, 1.0f,		0.0f,  1.0f,		//top left
};


GLuint Indices_Quad[] =
{
	0, 1, 2,
	0, 2, 3,
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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glViewport(0, 0, magic, magic);

	Program_Hex = ShaderLoader::CreateProgram("Resources/Shaders/ClipSpace.vs",
		"Resources/Shaders/Hexagon.fs");

	Program_Quad = ShaderLoader::CreateProgram("Resources/Shaders/ClipSpaceQuad.vs",
		"Resources/Shaders/Quad.fs");

	int ImageWidth;
	int ImageHeight;
	int ImageComponents;
	unsigned char* ImageData;


	stbi_set_flip_vertically_on_load(true);
	ImageData = stbi_load("Resources/Textures/Elige.png",
		&ImageWidth, &ImageHeight, &ImageComponents, 0);
	ImageGen(Elige);
	
	GLint LoadedComponents = (ImageComponents == 4) ? GL_RGBA : GL_RGB;
	
	glTexImage2D(GL_TEXTURE_2D, 0, LoadedComponents, ImageWidth, ImageHeight, 0,
		LoadedComponents, GL_UNSIGNED_BYTE, ImageData);
	
	glGenerateMipmap(GL_TEXTURE_2D);

	ImageClear(ImageData);





	stbi_set_flip_vertically_on_load(true);
	ImageData = stbi_load("Resources/Textures/Mood.jpg",
		&ImageWidth, &ImageHeight, &ImageComponents, 0);
	ImageGen(Mood);
	
	LoadedComponents = (ImageComponents == 4) ? GL_RGBA : GL_RGB;
	
	glTexImage2D(GL_TEXTURE_2D, 0, LoadedComponents, ImageWidth, ImageHeight, 0,
		LoadedComponents, GL_UNSIGNED_BYTE, ImageData);
	
	glGenerateMipmap(GL_TEXTURE_2D);
	
	ImageClear(ImageData);
	glBindTexture(GL_TEXTURE_2D, 0);




	stbi_set_flip_vertically_on_load(true);
	ImageData = stbi_load("Resources/Textures/Capguy_Walk.png",
		&ImageWidth, &ImageHeight, &ImageComponents, 0);
	ImageGen(AnimationSprite);

	LoadedComponents = (ImageComponents == 4) ? GL_RGBA : GL_RGB;

	glTexImage2D(GL_TEXTURE_2D, 0, LoadedComponents, ImageWidth, ImageHeight, 0,
		LoadedComponents, GL_UNSIGNED_BYTE, ImageData);

	glGenerateMipmap(GL_TEXTURE_2D);

	ImageClear(ImageData);
	glBindTexture(GL_TEXTURE_2D, 0);





	vaoGenerate(VAO_Hex);
	eboGenerate(EBO_Hex);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices_Hex), Indices_Hex, GL_STATIC_DRAW);
	vboGenerate(VBO_Hex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices_Hex), Vertices_Hex, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);





	vaoGenerate(VAO_Quad);
	eboGenerate(EBO_Quad);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices_Quad), Indices_Quad, GL_STATIC_DRAW);
	vboGenerate(VBO_Quad);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices_Quad), Vertices_Quad, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	PreviousTimeStep = (float)glfwGetTime();
}
void Update()
{
	glfwPollEvents();



	CurrentTime = (float)glfwGetTime();

	float CurrentTimeStep = (float)glfwGetTime();
	float DeltaTime = CurrentTimeStep - PreviousTimeStep;
	PreviousTimeStep = CurrentTimeStep;

	AnimationTimeX += DeltaTime;
	AnimationTimeY += DeltaTime;

	if (AnimationTimeX >= 0.1f)
	{
		PositionSpriteX += 0.125f;
		AnimationTimeX = 0.0f;
	}
	TranslationMat = glm::translate(glm::mat4(), ObjPositionRight);
	RotationMat = glm::rotate(glm::mat4(), glm::radians(ObjRotationAngle), glm::vec3(0.0f, 0.0f, 1.0f));
	ScaleMat = glm::scale(glm::mat4(), ObjScale);
	
	float halfWindowWidth = float(magic) * 0.5f;
	float halfWindowHeight = float(magic) * 0.5f;
	ProjectionMat = glm::ortho(-halfWindowWidth, halfWindowWidth, -halfWindowHeight, halfWindowHeight, 0.1f, 100.0f);

	ObjModelMat = TranslationMat * RotationMat * ScaleMat;
	
	ViewMat = glm::lookAt(CameraPos, CameraPos + CameraLookDir, CameraUpDir);

	PVMMatHexRight = ProjectionMat * ViewMat * ObjModelMat;




	TranslationMat = glm::translate(glm::mat4(), ObjPositionLeft);
	ObjModelMat = TranslationMat * RotationMat * ScaleMat;

	PVMMatHexLeft = ProjectionMat * ViewMat * ObjModelMat;



	TranslationMat = glm::translate(glm::mat4(), ObjPositionQuad);
	ObjModelMat = TranslationMat * RotationMat * ScaleMat;

	PVMMatQuad = ProjectionMat * ViewMat * ObjModelMat;

}
void Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(Program_Hex);
	glBindVertexArray(VAO_Hex);

	GLint CurrentTimeLoc = glGetUniformLocation(Program_Hex, "CurrentTime");
	glUniform1f(CurrentTimeLoc, CurrentTime);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Elige);
	glUniform1i(glGetUniformLocation(Program_Hex, "ImageTexture"), 0);
	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, Mood);
	glUniform1i(glGetUniformLocation(Program_Hex, "ImageTexture1"), 1);



	GLint PVMMatLoc = glGetUniformLocation(Program_Hex, "PVMMat");
	glUniformMatrix4fv(PVMMatLoc, 1, GL_FALSE, glm::value_ptr(PVMMatHexRight));

	glDrawElements(GL_TRIANGLES, sizeof(Indices_Hex), GL_UNSIGNED_INT, 0);



	glUniformMatrix4fv(PVMMatLoc, 1, GL_FALSE, glm::value_ptr(PVMMatHexLeft));

	glDrawElements(GL_TRIANGLES, sizeof(Indices_Hex), GL_UNSIGNED_INT, 0);




	glUseProgram(Program_Quad);
	glBindVertexArray(VAO_Quad);
	
	glUniform2f(glGetUniformLocation(Program_Quad, "TexOffset"), PositionSpriteX, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, AnimationSprite);
	glUniform1i(glGetUniformLocation(Program_Quad, "ImageTexture"), 0);

	GLint PVMMatLoc1 = glGetUniformLocation(Program_Quad, "PVMMat");
	glUniformMatrix4fv(PVMMatLoc1, 1, GL_FALSE, glm::value_ptr(PVMMatQuad));
	
	glDrawElements(GL_TRIANGLES, sizeof(Indices_Quad), GL_UNSIGNED_INT, 0);




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
void ImageClear(unsigned char* image)
{
	stbi_image_free(image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}