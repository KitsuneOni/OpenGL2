// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// 
// (c) 2021 Media Design School
//
// File Name   : Pyramid.h
// Description : A 3D Pyramid object class.
//				 Inherits from Mesh3D
// Author      : Neel Kolhe
// Mail        : Neel.Kolhe@mds.ac.nz

#pragma once
#include "Mesh3D.h"

class Pyramid : public Mesh3D
{
public:
	// Create the Pyramid Object
	Pyramid();

	// Render the Pyramid
	virtual void Draw();
	// Update the Pyramid Information
	virtual void Update(float DeltaTime);
	// Control the Pyramid with Key Inputs
	void ControlMovement(GLFWwindow* Window, float DeltaTime);


	std::vector<GLfloat> m_Vertices = {
		// Index	// Position				// Tex Coords	// Position Index
					// Bottom Quad
		/* 00 */	-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		/* 00 */
		/* 01 */	-0.5f, 0.0f,  0.5f,		0.0f, 0.0f,		/* 01 */
		/* 02 */	 0.5f, 0.0f,  0.5f,		1.0f, 0.0f,		/* 02 */
		/* 03 */	 0.5f, 0.0f, -0.5f,		1.0f, 1.0f,		/* 03 */
					// Side One
		/* 04 */	-0.5f, 0.0f, -0.5f,		0.0f, 0.0f,		/* 00 */
		/* 05 */	-0.5f, 0.0f,  0.5f,		1.0f, 0.0f,		/* 01 */
					// Side Two
		/* 06 */	-0.5f, 0.0f,  0.5f,		0.0f, 0.0f,		/* 01 */
		/* 07 */	 0.5f, 0.0f,  0.5f,		1.0f, 0.0f,		/* 02 */
					// Side Three
		/* 08 */	 0.5f, 0.0f,  0.5f,		0.0f, 0.0f,		/* 02 */
		/* 09 */	 0.5f, 0.0f, -0.5f,		1.0f, 0.0f,		/* 03 */
					// Side Four
		/* 10 */	 0.5f, 0.0f, -0.5f,		0.0f, 0.0f,		/* 03 */
		/* 11 */	-0.5f, 0.0f, -0.5f,		1.0f, 0.0f,		/* 00 */
					// Top Point
		/* 12 */	 0.0f, 0.5f,  0.0f,		0.5f, 1.0f,		/* 04 */
	};

	std::vector<GLuint> m_Indices = {
		1, 0, 3,	// Bottom Quad
		1, 3, 2,	// Bottom Quad

		4, 5, 12,
		6, 7, 12,
		8, 9, 12,
		10, 11, 12,
	};

};

