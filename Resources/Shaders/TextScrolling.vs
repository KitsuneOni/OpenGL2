#version 460 core

layout (location = 0) in vec4 Vertex;	// (vec2:Position, Vec2:TextCoords)

out vec2 FragTexCoords;
out vec2 VertexCopy;
out float leftClip;
out float rightClip;

uniform mat4 ProjectionMat;
uniform float CurrentTime;

void main()
{
	leftClip = 0;
	rightClip = 800;

	vec2 NewCoords = vec2(mod(Vertex.x + CurrentTime*50, rightClip - leftClip), Vertex.y);

	gl_Position = ProjectionMat * vec4(NewCoords, 0.0f, 1.0f);

	FragTexCoords = Vertex.zw;
	VertexCopy = NewCoords;
}