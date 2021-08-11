// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// 
// (c) 2021 Media Design School
//
// File Name   : ObjectFactory.h
// Description : A Class to create objects.
//				 Not neccessarily needed but found this design pattern recently and thought it would be cool to add.
// Author      : Neel Kolhe
// Mail        : Neel.Kolhe@mds.ac.nz

#pragma once
#include <memory>
#include <random>
#include "Mesh.h"
#include "LightManager.h"

#include "Cube.h"
#include "Quad.h"
#include "Pyramid.h"
#include "Sphere.h"

class ObjectFactory
{
public:
	// Returns a vector of spheres in random positions
	static std::vector<Sphere*> CreateSpheres(Camera* camera, LightManager* lightman, SkyBox* skybox, int NumberofSpheres, glm::vec2 ExtentsX, glm::vec2 ExtentsY, glm::vec2 ExtentsZ);

	// Returns a newly created cube.
	static Cube* CreateCube(const char* TextureName, const char* VertexShader, const char* FragmentShader, glm::vec3 Position, glm::vec3 Scale, Camera* camera, LightManager* lightman, SkyBox* skybox);
	// Returns a newly created Quad UI.
	static Quad* CreateHoverQuad(const char* TextureName, const char* HoverTextureName, const char* VertexShader, const char* FragmentShader, glm::vec3 Position, glm::vec3 Scale, Camera* camera);
	// Returns a newly created Pyramid.
	static Pyramid* CreatePyramid(const char* TextureName, const char* VertexShader, const char* FragmentShader, glm::vec3 Position, glm::vec3 Scale, Camera* camera);

};


