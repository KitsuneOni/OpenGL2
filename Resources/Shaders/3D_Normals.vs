#version 460 core

// Vertex Data
layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoords;
layout (location = 2) in vec3 Normal;

// Inputs
uniform mat4 PVM;
uniform mat4 Model;

// Output to Fragment Shader
out vec2 FragTexCoords;
out vec3 FragNormal;
out vec3 FragPos;

void main()
{
	// Calculate the Vertex Position
	gl_Position = PVM * vec4(Position, 1.0f);

	// Pass through the Vertex Information
	FragTexCoords = TexCoords;
	FragNormal = mat3(transpose(inverse(Model))) * Normal;
	FragPos = vec3(Model * vec4(Position, 1.0f));
}