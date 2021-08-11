#include "LightSphere.h"

LightSphere::LightSphere(glm::vec3 Position, glm::vec3 Color, Camera* cam) 
{
	SetObjPosition(Position);
	this->Color = Color;
	camera = cam;

	SetProgram("Resources/Shaders/3D_Normals.vs", "Resources/Shaders/StaticColor.fs");
}

void LightSphere::Draw()
{
	glUseProgram(m_Program);
	glBindVertexArray(VAO);

	glUniformMatrix4fv(glGetUniformLocation(m_Program, "PVM"), 1, GL_FALSE, glm::value_ptr(camera->ReturnPersPVM(m_ObjModelMat)));

	glUniformMatrix4fv(glGetUniformLocation(m_Program, "Model"), 1, GL_FALSE, glm::value_ptr(m_ObjModelMat));

	glUniform3fv(glGetUniformLocation(m_Program, "Color"), 1, glm::value_ptr(Color));

	glDrawElements(DrawType, IndexCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}
