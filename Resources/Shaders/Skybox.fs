#version 460 core

// Vertex Shader Inputs
//in vec3 FragColor;
in vec3 FragTexCoords;

// Uniform Inputs
uniform samplerCube Texture;

// Output
out vec4 FinalColor;

void main()
{
	FinalColor = texture(Texture, FragTexCoords); // * vec4(FragColor, 1.0f);
}