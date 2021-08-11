#version 460 core

layout (location = 0) in vec3 Position;

// Inputs
uniform mat4 PVM;

out vec3 FragTexCoords;

void main()
{
	gl_Position = PVM * vec4(Position, 1.0f);
	FragTexCoords = Position;
}