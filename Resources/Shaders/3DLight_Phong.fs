#version 460 core

// Vertex Shader Inputs
in vec2 FragTexCoords;
in vec3 FragNormal;
in vec3 FragPos;

// Uniform Inputs
uniform sampler2D ImageTexture0;
uniform vec3 CameraPos;
uniform float AmbientStrength		= 0.1f;
uniform vec3 AmbientColor			= vec3(1.0f, 1.0f, 1.0f);
uniform vec3 LightColor				= vec3(1.0f, 1.0f, 1.0f);
uniform vec3 LightPos               = vec3(-2.0f, 6.0f, 3.0f);
uniform float LightSpecularStrength = 1.0f;
uniform float Shininess             = 32.0f;

// Output
out vec4 FinalColor;

void main()
{
	// Light Direction
	vec3 Normal = normalize(FragNormal);
	vec3 LightDir = normalize(FragPos - LightPos);

	// Ambient Component
	vec3 Ambient = AmbientStrength * AmbientColor;

	// Diffuse Component
	float DiffuseStrength = max(dot(Normal, -LightDir), 0.0f);
	vec3 Diffuse = DiffuseStrength * LightColor;

	// Specular Component
	vec3 ReverseViewDirection = normalize(CameraPos - FragPos);
	vec3 ReflectedDir = reflect(LightDir, Normal);
	float SpecularReflectivity = pow(max(dot(ReverseViewDirection, ReflectedDir), 0.0f), Shininess);
	vec3 Specular = LightSpecularStrength * SpecularReflectivity * LightColor;

	// Combine the Lighting Component
	vec4 Light = vec4(Ambient + Diffuse + Specular, 1.0f);

	// Calculate
	FinalColor = Light * texture(ImageTexture0, FragTexCoords);
}