#include "LightManager.h"

LightManager::LightManager()
{
}

void LightManager::AddPointLight(int index, glm::vec3 Position, glm::vec3 Color, float AmbientStrength, float SpecularStrength, float AttenuationConstant, float AttenuationLinear, float AttenuationExponent)
{
	if (index < MAX_POINT_LIGHTS)
	{
		PointLights[index].Position = Position;
		PointLights[index].Color = Color;
		PointLights[index].AmbientStrength = AmbientStrength;
		PointLights[index].SpecularStrength = SpecularStrength;
		PointLights[index].AttenuationConstant = AttenuationConstant;
		PointLights[index].AttenuationLinear = AttenuationLinear;
		PointLights[index].AttenuationExponent = AttenuationExponent;
	}
	else
	{
		std::cout << "Index " << index << "out of range of Max Point Lights." << std::endl;
	}
}

void LightManager::SetDirectionalLight(glm::vec3 Direction, glm::vec3 Color, float AmbientStrength, float SpecularStrength)
{
	directionLight.Direction = Direction;
	directionLight.Color = Color;
	directionLight.AmbientStrength = AmbientStrength;
	directionLight.SpecularStrength = SpecularStrength;
}

void LightManager::SendLightDataToShader(GLuint Program)
{
	// Go through each light and pass the Light Information to the Shader
	for (int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		// Create the Location Information:
		std::string PositionShaderPos = ("PointLights[" + std::to_string(i) + "].Position");
		std::string ColorShaderPos = ("PointLights[" + std::to_string(i) + "].Color");
		std::string AmbientStrengthShaderPos = ("PointLights[" + std::to_string(i) + "].AmbientStrength");
		std::string SpecularStrengthShaderPos = ("PointLights[" + std::to_string(i) + "].SpecularStrength");
		std::string AttenuationConstantShaderPos = ("PointLights[" + std::to_string(i) + "].AttenuationConstant");
		std::string AttenuationLinearShaderPos = ("PointLights[" + std::to_string(i) + "].AttenuationLinear");
		std::string AttenuationExponentShaderPos = ("PointLights[" + std::to_string(i) + "].AttenuationExponent");

		// Pass to the Shader
		glUniform3fv(glGetUniformLocation(Program, PositionShaderPos.c_str()), 1, glm::value_ptr(PointLights[i].Position));
		glUniform3fv(glGetUniformLocation(Program, ColorShaderPos.c_str()), 1, glm::value_ptr(PointLights[i].Color));
		glUniform1f(glGetUniformLocation(Program, AmbientStrengthShaderPos.c_str()), PointLights[i].AmbientStrength);
		glUniform1f(glGetUniformLocation(Program, SpecularStrengthShaderPos.c_str()), PointLights[i].SpecularStrength);
		glUniform1f(glGetUniformLocation(Program, AttenuationConstantShaderPos.c_str()), PointLights[i].AttenuationConstant);
		glUniform1f(glGetUniformLocation(Program, AttenuationLinearShaderPos.c_str()), PointLights[i].AttenuationLinear);
		glUniform1f(glGetUniformLocation(Program, AttenuationExponentShaderPos.c_str()), PointLights[i].AttenuationExponent);
	}

	glUniform3fv(glGetUniformLocation(Program, "DirectLight.Direction"), 1, glm::value_ptr(directionLight.Direction));
	glUniform3fv(glGetUniformLocation(Program, "DirectLight.Color"), 1, glm::value_ptr(directionLight.Color));
	glUniform1f(glGetUniformLocation(Program, "DirectLight.AmbientStrength"), directionLight.AmbientStrength);
	glUniform1f(glGetUniformLocation(Program, "DirectLight.SpecularStrength"), directionLight.SpecularStrength);
}

LightManager::PointLight LightManager::ReturnPointLight(int index)
{
	return PointLights[index];
}


