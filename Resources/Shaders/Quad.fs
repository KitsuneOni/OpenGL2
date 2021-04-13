#version 460 core

in vec3 FragColor;
in vec2 FragTexCoords;
in vec2 TexPosition;

uniform float CurrentTime;
uniform sampler2D ImageTexture;
uniform sampler2D ImageTexture1;

out vec4 FinalColor;

void main()
{
    FinalColor = texture(ImageTexture, FragTexCoords);

}