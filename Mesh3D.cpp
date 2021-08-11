#include "Mesh3D.h"

void Mesh3D::SetTexture(const char* TextureName)
{
	m_Texture = TextureLoader::CreateTexture(TextureName);
}

void Mesh3D::SetObjPosition(glm::vec3 objPos)
{
	// After setting the position, It resets the Model Matrix
	m_ObjPosition = objPos;
	SetObjModelMat();
}

void Mesh3D::SetObjScale(glm::vec3 ObjScale)
{
	// After setting the Scale, It resets the Model Matrix
	m_ObjScale = ObjScale;
	SetObjModelMat();
}

void Mesh3D::SetObjRotation(float ObjRotation)
{
	// After setting the Rotation, It resets the Model Matrix
	m_ObjRotation = ObjRotation;
	SetObjModelMat();
}

void Mesh3D::SetObjModelMat()
{
	// Calculates the new Model Matrix
	m_TranslationMat = glm::translate(glm::mat4(), m_ObjPosition);
	m_RotationMat = glm::rotate(glm::mat4(), glm::radians(m_ObjRotation), glm::vec3(1.0f, 0.0f, 1.0f));
	m_ScaleMat = glm::scale(glm::mat4(), m_ObjScale);

	m_ObjModelMat = m_TranslationMat * m_RotationMat * m_ScaleMat;
}
