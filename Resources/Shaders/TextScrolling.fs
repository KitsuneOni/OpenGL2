#version 460 core

in vec2 FragTexCoords;
in vec2 VertexCopy;
in float leftClip;
in float rightClip;

uniform sampler2D TextTexture;
uniform vec3 TextColor;

out vec4 FinalColor;

void main()
{
	float Alpha = texture(TextTexture, FragTexCoords).r;

	if (VertexCopy.x < (leftClip + 50) || VertexCopy.x > (rightClip - 50)){
		Alpha = 0.0f;	
	}


	FinalColor = vec4(TextColor, Alpha);
}