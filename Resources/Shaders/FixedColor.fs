#version 460 core

in vec3 FragColor;
in vec2 FragTexCoords;

uniform float CurrentTime;
uniform sampler2D ImageTexture;
uniform sampler2D ImageTexture1;

out vec4 FinalColor;

void main()
{
    FinalColor = mix(texture(ImageTexture, FragTexCoords) , texture(ImageTexture1, FragTexCoords), (sin(CurrentTime)+ 1)/2);

}