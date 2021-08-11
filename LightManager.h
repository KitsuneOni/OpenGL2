#pragma once
// System
#include <iostream>
#include <vector>
#include <string>
// OpenGL
#include <glew.h>
#include <glfw3.h>
// Math
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class LightManager
{
	static const int MAX_POINT_LIGHTS = 4;

	struct PointLight
	{
		glm::vec3 Position;
		glm::vec3 Color;
		float AmbientStrength = NULL;
		float SpecularStrength;

		float AttenuationConstant;
		float AttenuationLinear;
		float AttenuationExponent;
	};

	struct DirectionalLight
	{
		glm::vec3 Direction;
		glm::vec3 Color;
		float AmbientStrength;
		float SpecularStrength;
	};

public:

	LightManager();

	void AddPointLight(int index, glm::vec3 Position, glm::vec3 Color, float AmbientStrength, float SpecularStrength, float AttenuationConstant, float AttenuationLinear, float AttenuationExponent);
	void SetDirectionalLight(glm::vec3 Direction, glm::vec3 Color, float AmbientStrength, float SpecularStrength);

	void SendLightDataToShader(GLuint Program);

	PointLight ReturnPointLight(int index);
private:
	
	PointLight PointLights[MAX_POINT_LIGHTS];
	DirectionalLight directionLight;
};

