#version 460 core

// Vertex Data Interpretation
layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoords;

// Inputs
uniform mat4 pvmMat;
uniform vec2 texOffset;


// Outputs to Fragment Shader
out vec2 FragTexCoords;

void main()
{
	gl_Position = pvmMat * vec4(Position, 1.0f);
	FragTexCoords = TexCoords + texOffset;
}