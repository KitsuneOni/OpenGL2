#include "Pyramid.h"

Pyramid::Pyramid()
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
}

void Pyramid::Draw()
{
	glUseProgram(m_Program);
	glBindVertexArray(mVAO);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glUniform1i(glGetUniformLocation(m_Program, "ImageTexture"), 0);

	GLint PVMMatLoc = glGetUniformLocation(m_Program, "pvmMat");
	glUniformMatrix4fv(PVMMatLoc, 1, GL_FALSE, glm::value_ptr(camera->ReturnPersPVM(m_ObjModelMat)));

	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void Pyramid::Update(float DeltaTime)
{
}

void Pyramid::ControlMovement(GLFWwindow* Window, float DeltaTime)
{
	// Take the input from each direction and store it as a Direction Vector.
	glm::vec3 Direction = glm::vec3(0.0f, 0.0f, 0.0f);
	if (glfwGetKey(Window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Direction.z += 1.0f;
	}

	if(glfwGetKey(Window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Direction.z += -1.0f;
	}

	if (glfwGetKey(Window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Direction.x += 1.0f;
	}

	if (glfwGetKey(Window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Direction.x -= 1.0f;
	}

	if (glfwGetKey(Window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		Direction.y += 1.0f;
	}

	if (glfwGetKey(Window, GLFW_KEY_E) == GLFW_PRESS)
	{
		Direction.y -= 1.0f;
	}

	// Normalize the Direction 
	// Then Set object position to its movement.
	if (Direction != glm::vec3(0.0f, 0.0f, 0.0f))
	{
		Direction = glm::normalize(Direction);
		glm::vec3 Movement = Direction * 10.0f * DeltaTime;
		SetObjPosition(m_ObjPosition + Movement);
	}
	
}
