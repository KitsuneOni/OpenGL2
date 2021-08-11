#version 460 core

// Vertex Shader Inputs
//in vec3 FragColor;
in vec2 FragTexCoords;

// Uniform Inputs
uniform sampler2D ImageTexture;

uniform vec3 Color;

// Output
out vec4 FinalColor;

void main()
{
	FinalColor = vec4(Color, 1.0f); // * vec4(FragColor, 1.0f);
}