// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// 
// (c) 2021 Media Design School
//
// File Name   : TextureLoader.h
// Description : A class to load in new textures. Will store the textures and reuse them if they get attempted to be created again
// Author      : Neel Kolhe
// Mail        : Neel.Kolhe@mds.ac.nz
#pragma once

// Library Includes
#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <map>


class TextureLoader
{
public:
	// Static Function to create a new texture
	static GLuint CreateTexture(const char* TextureFileName);

private:
	// Constructor
	TextureLoader();
	// Destructor
	~TextureLoader();

	// A map to handle all created textures
	static std::map <const char*, GLuint> textureMap;
};

