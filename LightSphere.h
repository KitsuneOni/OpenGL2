#pragma once
#include "Sphere.h"
class LightSphere : public Sphere
{
public:
	LightSphere(glm::vec3 Position, glm::vec3 Color, Camera* cam);

	void Draw();

private:
	glm::vec3 Color;
};

