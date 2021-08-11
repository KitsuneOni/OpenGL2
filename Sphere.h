#pragma once

#include <glew.h>
#include <glfw3.h>

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

#include "Mesh3D.h"

#include "LightManager.h"
#include "SkyBox.h"


class Sphere : public Mesh3D
{
public:
	Sphere() : Sphere(0.5f, 10) {};
	Sphere(float Radius, int Fidelity);
	~Sphere();


	// Inherited via Mesh3D
	virtual void Draw() override;
	virtual void Update(float DeltaTime) override;

	void SetLightManager(LightManager* lightManager);

	SkyBox* skybox = nullptr;
 
protected:
	GLuint VAO;

	int IndexCount;
	int DrawType;

	LightManager* LightMan = nullptr;

};

