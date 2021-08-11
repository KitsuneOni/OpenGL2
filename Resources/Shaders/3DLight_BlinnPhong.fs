#version 460 core

struct DirectionalLight
{
	vec3 Direction;
	vec3 Color;
	float AmbientStrength;
	float SpecularStrength;
};

struct PointLight
{
	vec3 Position;
	vec3 Color;
	float AmbientStrength;
	float SpecularStrength;

	float AttenuationConstant;
	float AttenuationLinear;
	float AttenuationExponent;
};

#define MAX_POINT_LIGHTS 4


// Vertex Shader Inputs
in vec2 FragTexCoords;
in vec3 FragNormal;
in vec3 FragPos;

// Uniform Inputs
uniform sampler2D ImageTexture0;
uniform vec3 CameraPos;
//uniform float AmbientStrength		= 0.1f;
uniform vec3 AmbientColor			= vec3(1.0f, 1.0f, 1.0f);
//uniform vec3 LightColor				= vec3(1.0f, 1.0f, 1.0f);
//uniform vec3 LightPos               = vec3(-2.0f, 6.0f, 3.0f);
uniform float LightSpecularStrength = 1.0f;
uniform float Shininess             = 32.0f;

uniform PointLight PointLights[MAX_POINT_LIGHTS];
uniform DirectionalLight DirectLight;


// Output
out vec4 FinalColor;

vec3 CalculateLight_Point(PointLight pLight)
{
	// Light Direction
	vec3 Normal = normalize(FragNormal);
	vec3 LightDir = normalize(FragPos - pLight.Position);

	// Ambient Component
	vec3 Ambient = pLight.AmbientStrength * AmbientColor;

	// Diffuse Component
	float DiffuseStrength = max(dot(Normal, -LightDir), 0.0f);
	vec3 Diffuse = DiffuseStrength * pLight.Color;

	// Specular Component
	vec3 ReverseViewDirection = normalize(CameraPos - FragPos);
	vec3 HalfwayVector = normalize(-LightDir + ReverseViewDirection);
	float SpecularReflectivity = pow(max(dot(Normal, HalfwayVector), 0.0f), Shininess);
	vec3 Specular = LightSpecularStrength * SpecularReflectivity * pLight.Color;

	// Combine the Lights
	vec3 CombinedLight = Ambient + Diffuse + Specular;

	// Calculate and Apply the Attenuation
	float Distance = length(pLight.Position - FragPos);
	float Attenuation = pLight.AttenuationConstant + (pLight.AttenuationLinear * Distance) + (pLight.AttenuationExponent * pow(Distance, 2));

	CombinedLight /= Attenuation;

	return CombinedLight;
}

vec3 CalculateLight_Directional(DirectionalLight dLight)
{
	// Light Direction
	vec3 Normal = normalize(FragNormal);
	vec3 LightDir = normalize(dLight.Direction);

	// Ambient Component
	vec3 Ambient = dLight.AmbientStrength * AmbientColor;

	// Diffuse Component
	float DiffuseStrength = max(dot(Normal, -LightDir), 0.0f);
	vec3 Diffuse = DiffuseStrength * dLight.Color;

	// Specular Component
	vec3 ReverseViewDirection = normalize(CameraPos - FragPos);
	vec3 HalfwayVector = normalize(-LightDir + ReverseViewDirection);
	float SpecularReflectivity = pow(max(dot(Normal, HalfwayVector), 0.0f), Shininess);
	vec3 Specular = LightSpecularStrength * SpecularReflectivity * dLight.Color;

	// Combine the Lights
	vec3 CombinedLight = Ambient + Diffuse + Specular;

	return CombinedLight;
}

void main()
{
	// Calculate
	
	// Calculate each of the Point Lights and add the Results
	vec3 LightOutput = vec3(0.0f, 0.0f, 0.0f);
	
	for (int i = 0; i < MAX_POINT_LIGHTS; i++)
	{	
		LightOutput += CalculateLight_Point(PointLights[i]);
	}

	LightOutput += CalculateLight_Directional(DirectLight);


	FinalColor = vec4(LightOutput, 1.0f) * texture(ImageTexture0, FragTexCoords);
}

