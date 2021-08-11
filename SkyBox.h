#pragma once
#include "Mesh3D.h"
#include "Dependencies/STB/stb_image.h"

class SkyBox : public Mesh3D
{
public:
	SkyBox(Camera* camera, const char* SkyBoxTexture[6]);
	
	virtual void Update(float DeltaTime) override;

	virtual void Draw() override;

	void GenerateSkyboxTextures(const char* SkyBoxTexture[6]);

	GLuint GetTexture();

private:
	std::vector<GLfloat> m_Vertices = {
		// Index	// Position				// Position Index
				// Front Quad
		/* 00 */	-0.5f,  0.5f,  0.5f,	
		/* 01 */	-0.5f, -0.5f,  0.5f,	
		/* 02 */	 0.5f, -0.5f,  0.5f,	
		/* 03 */	 0.5f,  0.5f,  0.5f,	
				// Back Quad
		/* 04 */	 0.5f,  0.5f, -0.5f,	
		/* 05 */	 0.5f, -0.5f, -0.5f,	
		/* 06 */	-0.5f, -0.5f, -0.5f,	
		/* 07 */	-0.5f,  0.5f, -0.5f,	
				// Right Quad
		/* 08 */	 0.5f,  0.5f,  0.5f,	
		/* 09 */	 0.5f, -0.5f,  0.5f,	
		/* 10 */	 0.5f, -0.5f, -0.5f,	
		/* 11 */	 0.5f,  0.5f, -0.5f,	
				// Left Quad
		/* 12 */	-0.5f,  0.5f, -0.5f,	
		/* 13 */	-0.5f, -0.5f, -0.5f,	
		/* 14 */	-0.5f, -0.5f,  0.5f,	
		/* 15 */	-0.5f,  0.5f,  0.5f,	
				// Top Quad
		/* 16 */	-0.5f,  0.5f, -0.5f,	
		/* 17 */	-0.5f,  0.5f,  0.5f,
		/* 18 */	 0.5f,  0.5f,  0.5f,	
		/* 19 */	 0.5f,  0.5f, -0.5f,	
				// Bottom Quad
		/* 20 */	-0.5f, -0.5f,  0.5f,	
		/* 21 */	-0.5f, -0.5f, -0.5f,	
		/* 22 */	 0.5f, -0.5f, -0.5f,	
		/* 23 */	 0.5f, -0.5f,  0.5f,
	};

	std::vector<GLuint> m_Indices = {
		 0,  2, 1,
		 0,  3, 2,
		 4,  6, 5,
		 4,  7, 6,
		 8, 10, 9,
		 8, 11, 10,
		12, 14, 13,
		12, 15, 14,
		16, 18, 17,
		16, 19, 18,
		20, 22, 21,
		20, 23, 22,
	};

	glm::mat4 m_PVM;
};

