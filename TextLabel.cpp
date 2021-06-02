#include "TextLabel.h"

TextLabel::TextLabel(std::string Text,	std::string Font,	glm::ivec2 PixelSize,	glm::vec2 Pos,	glm::vec3 Color = glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2 Scale = glm::vec2(1.0f, 1.0f))
{
	SetText(Text);
	SetColor(Color);
	SetPosition(Pos);
	SetScale(Scale);

	ProjectionMat = glm::ortho(0.0f, 800.0f, 0.0f, 800.0f, 0.1f, 100.0f);
};