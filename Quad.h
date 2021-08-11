// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// 
// (c) 2021 Media Design School
//
// File Name   : Quad.h
// Description : A 2D Quad.
//				 Inherits from Mesh3D [Realised too late that it needs the functionality from it]
// Author      : Neel Kolhe
// Mail        : Neel.Kolhe@mds.ac.nz
#pragma once
#include "Mesh3D.h"

class Quad : public Mesh3D
{
public:
	// Create the Quad
	Quad();

	// Render the Quad
	virtual void Draw();
	// Update the Quad
	virtual void Update(float DeltaTime);
	// Set the Texture for when Hovering over the quad
	void SetHoverTexture(const char* NewTexture);
	// Check if the position is inside the quad
	void isInsideQuad(double xPos, double yPos);

	std::vector<GLfloat> m_Vertices = {

		// Index	// Position				// Texture Coords
		/*  0  */   -0.5f,  0.5f, 0.0f,		0.0f, 1.0f,		// Top - Left
		/*  1  */	-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		// Bot - Left
		/*  2  */    0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		// Bot - Right
		/*  3  */    0.5f,  0.5f, 0.0f,    	1.0f, 1.0f,		// Top - Right
	};

	std::vector<GLuint> m_Indices =
	{
		0, 1, 2, // First Triangle  (TL -> BL -> BR)
		0, 2, 3, // Second Triangle (TL -> BR -> TR)
	};

private:
	// The Texture for the Hovered Texture
	GLuint m_2ndTexture;
	// Is Hovered
	bool Hovered;
};

