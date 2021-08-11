// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// 
// (c) 2021 Media Design School
//
// File Name   : Cube.h
// Description : A 3D Cube object class.
//				 Inherits from Mesh3D
// Author      : Neel Kolhe
// Mail        : Neel.Kolhe@mds.ac.nz

#pragma once
#include "Mesh3D.h"
#include "LightManager.h"
#include "SkyBox.h"

class Cube : public Mesh3D
{
public:
	// Create the Cube Information
	Cube();

	// Draw the Cube.
	virtual void Draw();
	// Update the Cubes information
	virtual void Update(float DeltaTime);
	void SetLightManager(LightManager* lightManager);

	std::vector<GLfloat> m_Vertices = {
		// Index	// Position				// Tex Coords	// Normals				// Position Index
				// Front Quad
		/* 00 */	-0.5f,  0.5f,  0.5f,	0.0f, 1.0f,		0.0f, 0.0f, 1.0f,/* 00 */
		/* 01 */	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,		0.0f, 0.0f, 1.0f, /* 01 */
		/* 02 */	 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,		0.0f, 0.0f, 1.0f,/* 02 */
		/* 03 */	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f,		0.0f, 0.0f, 1.0f,/* 03 */
				// Back Quad
		/* 04 */	 0.5f,  0.5f, -0.5f,	0.0f, 1.0f,		0.0f,0.0f,-1.0f,/* 04 */
		/* 05 */	 0.5f, -0.5f, -0.5f,	0.0f, 0.0f,		0.0f,0.0f,-1.0f,/* 05 */
		/* 06 */	-0.5f, -0.5f, -0.5f,	1.0f, 0.0f,		0.0f,0.0f,-1.0f,/* 06 */
		/* 07 */	-0.5f,  0.5f, -0.5f,	1.0f, 1.0f,		0.0f,0.0f,-1.0f,/* 07 */
				// Right Quad
		/* 08 */	 0.5f,  0.5f,  0.5f,	0.0f, 1.0f,		1.0f,0.0f,0.0f,/* 03 */
		/* 09 */	 0.5f, -0.5f,  0.5f,	0.0f, 0.0f,		1.0f,0.0f,0.0f,/* 02 */
		/* 10 */	 0.5f, -0.5f, -0.5f,	1.0f, 0.0f,		1.0f,0.0f,0.0f,/* 05 */
		/* 11 */	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,		1.0f,0.0f,0.0f,/* 04 */
				// Left Quad
		/* 12 */	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,		-1.0f,0.0f,0.0f,/* 07 */
		/* 13 */	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,		-1.0f,0.0f,0.0f,/* 06 */
		/* 14 */	-0.5f, -0.5f,  0.5f,	1.0f, 0.0f,		-1.0f,0.0f,0.0f,/* 01 */
		/* 15 */	-0.5f,  0.5f,  0.5f,	1.0f, 1.0f,		-1.0f,0.0f,0.0f,/* 00 */
				// Top Quad
		/* 16 */	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,		0.0f,1.0f,0.0f,/* 07 */
		/* 17 */	-0.5f,  0.5f,  0.5f,	0.0f, 0.0f,		0.0f,1.0f,0.0f,/* 00 */
		/* 18 */	 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,		0.0f,1.0f,0.0f,/* 03 */
		/* 19 */	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,		0.0f,1.0f,0.0f,/* 04 */
				// Bottom Quad
		/* 20 */	-0.5f, -0.5f,  0.5f,	0.0f, 1.0f,		0.0f,-1.0f,0.0f,/* 01 */
		/* 21 */	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,		0.0f,-1.0f,0.0f,/* 06 */
		/* 22 */	 0.5f, -0.5f, -0.5f,	1.0f, 0.0f,		0.0f,-1.0f,0.0f,/* 05 */
		/* 23 */	 0.5f, -0.5f,  0.5f,	1.0f, 1.0f,		0.0f,-1.0f,0.0f,/* 02 */
	};

	std::vector<GLuint> m_Indices = {
		 0,  1, 2,
		 0,  2, 3,
		 4,  5, 6,
		 4,  6, 7,
		 8,  9, 10,
		 8, 10, 11,
		12, 13, 14,
		12, 14, 15,
		16, 17, 18,
		16, 18, 19,
		20, 21, 22,
		20, 22, 23,
	};

	// The Offset for the rotation
	float offset = 5;

	LightManager* LightMan = nullptr;
	GLuint ReflectionMap;
	SkyBox* sky;
};

