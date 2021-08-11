#include "Mesh.h"

void Mesh::SetProgram(const char* vertexShader, const char* fragmentShader)
{
	// Creates the Program and Stores it
	m_Program = ShaderLoader::CreateProgram(vertexShader, fragmentShader);
}

void Mesh::SetCamera(Camera* newCamera)
{
	camera = newCamera;
}
