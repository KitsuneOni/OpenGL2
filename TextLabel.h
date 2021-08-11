// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// 
// (c) 2021 Media Design School
//
// File Name   : TextLabel.h
// Description : A Text Label class, Loads the font and draws the text
//				 Allows for different styles [Scrolling Text, Stationary Text, Scale Bouncing]
// Author      : Neel Kolhe
// Mail        : Neel.Kolhe@mds.ac.nz

#pragma once
// Dependencies
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

// Library Includes
#include <map>
#include <string>
#include <iostream>
#include <vector>

// Local
#include "ShaderLoader.h"
#include "Utiliy.h"
#include "Mesh.h"

class TextLabel : public Mesh
{
public:
	// Generate the Text label
	TextLabel(std::string Text, std::string Font, glm::ivec2 PixelSize, glm::vec2 Pos, int Style, Camera* newCamera, glm::vec3 Color = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2 Scale = glm::vec2(1.0f, 1.0f));

	~TextLabel() {};

	// Render the Text
	virtual void Draw();
	// Update the Text
	virtual void Update(float DeltaTime);
	// Set the New Text string
	void SetText(std::string Text) { this->TextStr = Text; };
	// Set the New Color
	void SetColor(glm::vec3 Color) { this->Color = Color; };
	// Set the new Scale
	void SetScale(glm::vec2 Scale) { this->Scale = Scale; };
	// Set The Position
	void SetPosition(glm::vec2 Position) { this->Position = Position; };
	// Find the Text Center by going through the entire text string
	glm::vec2 FindCenterOfText();


protected:
	struct FontChar
	{
		GLuint TextureID = 0;	// Texture ID
		glm::ivec2 Size;		// Size of the glyph
		glm::ivec2 Bearing;		// Offset of the Glyph (top left) from the base line
		GLuint Advance = 0;		// How far to move for the next character
	};

	// Generate the Texture
	GLuint GenerateTexture(FT_Face face);

	static const int FontCharacterLimit = 128;
	bool Initialized = false;

	std::string TextStr;
	glm::vec2 Scale;
	glm::vec3 Color;
	glm::vec2 Position;

	std::vector<GLuint> m_Indices
	{
		0, 1, 2,
		0, 2, 3,
	};

	glm::mat4 ProjectionMatrix;
	std::map<GLchar, FontChar> CharacterMap;

	bool doScaling = false;
};

