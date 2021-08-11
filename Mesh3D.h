// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// 
// (c) 2021 Media Design School
//
// File Name   : Mesh3D.h
// Description : The mesh which handles more common things between each 3D shape.
//				 Reduces the duplicated code required for different 3D objects.
//				 Inherits from Mesh.h
// Author      : Neel Kolhe
// Mail        : Neel.Kolhe@mds.ac.nz

#pragma once
#include "Mesh.h"
#include "TextureLoader.h"
#include <vector>

class Mesh3D : public Mesh
{
public:
	// Virtual Function to Render the object. Gets overloaded when inherited.
	virtual void Draw() = 0;
	// Virtual Function to Update the object. Gets overloaded when inherited.
	virtual void Update(float DeltaTime) = 0;
	// Sets the texture of the object
	virtual void SetTexture(const char* TextureName);
	// Sets the Object Postion
	virtual void SetObjPosition(glm::vec3 objPos);
	// Sets the Object Scale
	virtual void SetObjScale(glm::vec3 ObjScale);
	// Sets the Object Rotation
	virtual void SetObjRotation(float ObjRotation);
	// Sets the Object Model Matrix
	virtual void SetObjModelMat();

protected:
	// Vertices for the Shape
	std::vector<GLfloat>  m_Vertices;
	// Indices for the Shape
	std::vector<GLuint > m_Indices;

	// Texture being Used
	GLuint m_Texture;

	// Location Informations
	glm::vec3 m_ObjPosition = { 0, 0, 0 };
	glm::vec3 m_ObjScale = { 1, 1, 1, };
	float m_ObjRotation = 0;

	// Matrix Informations
	glm::mat4 m_TranslationMat;
	glm::mat4 m_RotationMat;
	glm::mat4 m_ScaleMat;
	glm::mat4 m_ObjModelMat;
};

