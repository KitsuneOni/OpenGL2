#include "SkyBox.h"

SkyBox::SkyBox(Camera* camera, const char* SkyBoxTexture[6])
{
	SetCamera(camera);

	SetProgram("Resources/Shaders/Skybox.vs", "Resources/Shaders/Skybox.fs");
	
	GenerateSkyboxTextures(SkyBoxTexture);

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);


}

void SkyBox::Update(float DeltaTime)
{
	SetObjScale(glm::vec3(2000.0f, 2000.0f, 2000.0f));
	//m_ObjModelMat = glm::scale(glm::mat4(), );
	m_PVM = camera->ReturnPersPVM(m_ObjModelMat);
}

void SkyBox::Draw()
{
	glUseProgram(m_Program);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_Texture);
	glUniform1i(glGetUniformLocation(m_Program, "Texture"), 0);
	glUniformMatrix4fv(glGetUniformLocation(m_Program, "PVM"), 1, GL_FALSE, glm::value_ptr(m_PVM));

	glBindVertexArray(mVAO);
	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glUseProgram(0);
}

void SkyBox::GenerateSkyboxTextures(const char* SkyBoxTexture[6])
{
	glGenTextures(1, &m_Texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_Texture);

	// Load Image data
	int ImageWidth;
	int ImageHeight;
	int ImageComponents;
	stbi_set_flip_vertically_on_load(false);

	for (int i = 0; i < 6; i++)
	{
		//std::cout << "TEXTURE: " << SkyBoxTexture[i];
		std::string FullFilePath = "Resources/Textures/Cubemaps/" + (std::string)SkyBoxTexture[i];
		unsigned char* ImageData = stbi_load(FullFilePath.c_str(), &ImageWidth, &ImageHeight, &ImageComponents, 0);

		GLint LoadedComponents = (ImageComponents == 4) ? GL_RGBA : GL_RGB;

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, LoadedComponents, ImageWidth, ImageHeight, 0, LoadedComponents, GL_UNSIGNED_BYTE, ImageData);

		stbi_image_free(ImageData);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

GLuint SkyBox::GetTexture()
{
	return m_Texture;
}
