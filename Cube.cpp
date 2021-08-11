#include "Cube.h"

Cube::Cube()
{
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	// Generate EBO for Renderable Object
	glGenBuffers(1, &mEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(GLuint), m_Indices.data(), GL_STATIC_DRAW);

	// Generate VBO for Renderable Object
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(GLfloat), m_Vertices.data(), GL_STATIC_DRAW);

	// Set Vertex Information for the Renderable Object
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	ReflectionMap = TextureLoader::CreateTexture("Resources/Textures/Crate-Reflection.png");
}


void Cube::Draw()
{
	glUseProgram(m_Program);
	glBindVertexArray(mVAO);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glUniform1i(glGetUniformLocation(m_Program, "ImageTexture"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, ReflectionMap);
	glUniform1i(glGetUniformLocation(m_Program, "ReflectionMap"), 1);

	GLint PVMMatLoc = glGetUniformLocation(m_Program, "PVM");
	glUniformMatrix4fv(PVMMatLoc, 1, GL_FALSE, glm::value_ptr(camera->ReturnPersPVM(m_ObjModelMat)));

	glUniformMatrix4fv(glGetUniformLocation(m_Program, "Model"), 1, GL_FALSE, glm::value_ptr(m_ObjModelMat));
	glUniform3fv(glGetUniformLocation(m_Program, "CameraPos"), 1, glm::value_ptr(camera->returnCameraPosition()));

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_CUBE_MAP, sky->GetTexture());
	glUniform1i(glGetUniformLocation(m_Program, "Skybox"), 2);


	LightMan->SendLightDataToShader(m_Program);

	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void Cube::Update(float DeltaTime)
{
	// Rotate the Cube around its center
	SetObjRotation(m_ObjRotation + 1);

	// Orbit the centre of the world
	GLfloat x = offset * cos((float)glfwGetTime());
	GLfloat z = offset * sin((float)glfwGetTime());
	
	SetObjPosition(glm::vec3(x, m_ObjPosition.y, z));

}

void Cube::SetLightManager(LightManager* lightManager)
{
	LightMan = lightManager;
}
