#include "Quad.h"

Quad::Quad()
{
	// Generate the VAO
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

void Quad::Draw()
{
	glUseProgram(m_Program);
	glBindVertexArray(mVAO);

	glActiveTexture(GL_TEXTURE0);

	// Set the Texture based on if it is hovered over or not
	if (!Hovered)
	{
		glBindTexture(GL_TEXTURE_2D, m_Texture);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, m_2ndTexture);
	}

	glUniform1i(glGetUniformLocation(m_Program, "ImageTexture"), 0);

	GLint PVMMatLoc = glGetUniformLocation(m_Program, "pvmMat");
	glUniformMatrix4fv(PVMMatLoc, 1, GL_FALSE, glm::value_ptr(camera->ReturnOrthPVM() * m_ObjModelMat));

	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void Quad::Update(float DeltaTime)
{
}

void Quad::SetHoverTexture(const char* NewTexture)
{
	m_2ndTexture = TextureLoader::CreateTexture(NewTexture);
}

void Quad::isInsideQuad(double xPos, double yPos)
{	
	Hovered = (xPos > m_ObjPosition.x - (m_ObjScale.x / 2) && yPos < Utils::WindowHeight - (m_ObjPosition.y - m_ObjScale.y / 2) && xPos < m_ObjPosition.x + (m_ObjScale.x / 2) && yPos > Utils::WindowHeight - (m_ObjPosition.y  + (m_ObjScale.y / 2)));
}

