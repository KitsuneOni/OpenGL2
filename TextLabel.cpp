#include "TextLabel.h"

TextLabel::TextLabel(std::string Text, std::string Font, glm::ivec2 PixelSize, glm::vec2 Pos, int Style, Camera* newCamera, glm::vec3 Color, glm::vec2 Scale)
{
	SetText(Text);
	SetColor(Color);
	SetScale(Scale);
	SetPosition(Pos);
	SetCamera(newCamera);

	ProjectionMatrix = glm::ortho(0.0f, (GLfloat)Utils::WindowWidth, 0.0f, (GLfloat)Utils::WindowHeight, 0.0f, 100.0f);

	// A Switch to set the style of the text
	switch (Style)
	{
	case 0:
		// Normal Text
		SetProgram("Resources/Shaders/Text.vs", "Resources/Shaders/Text.fs");
		break;
	case 1:
		// Scrolling Text
		SetProgram("Resources/Shaders/TextScrolling.vs", "Resources/Shaders/TextScrolling.fs");
		break;
	case 2:
		// Scaling Text
		SetProgram("Resources/Shaders/Text.vs", "Resources/Shaders/Text.fs");
		doScaling = true;
		break;
	default:
		break;
	}

	FT_Library FontLibrary; // Font Library Object to load the font
	FT_Face FontFace;		// Each Character is called a glyph and Face is the collection of Glyphs


	// Initiate the Font Library
	if (FT_Init_FreeType(&FontLibrary) != 0)
	{
		std::cout << "FreeType Error: Could not init FreeType Library" << std::endl;
		return;
	}

	// Load the Font as a face
	if (FT_New_Face(FontLibrary, Font.c_str(), 0, &FontFace) != 0)
	{
		std::cout << "FreeType Error: Failed to Load Font: " << Font << std::endl;
		return;
	}

	FT_Set_Pixel_Sizes(FontFace, PixelSize.x, PixelSize.y);	// Set Size to load the Glyph as
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);					// Disable Byte-alignment Restriction

	// Load the Characters for the font up to the font charcter limit
	for (GLubyte Glyph = 0; Glyph < FontCharacterLimit; Glyph++)
	{
		// Load the Character Glyph into face
		if (FT_Load_Char(FontFace, Glyph, FT_LOAD_RENDER))
		{
			std::cout << "FreeType Error: Failed to Load Glyph: " << (unsigned char)Glyph << std::endl;
			continue;
		}

		// Now to Store Character for later use
		FontChar FontCharcter = {
			GenerateTexture(FontFace),	// Generate Texture for each character
			glm::ivec2(FontFace->glyph->bitmap.width, FontFace->glyph->bitmap.rows),
			glm::ivec2(FontFace->glyph->bitmap_left, FontFace->glyph->bitmap_top),
			(GLuint)FontFace->glyph->advance.x / 64 // Advanced is number of 1/64 pixels -> convert to pixels
		};
		CharacterMap.insert(std::pair<GLchar, FontChar>(Glyph, FontCharcter));
	}

	// Destroy FreeType Objects
	FT_Done_Face(FontFace);
	FT_Done_FreeType(FontLibrary);


	// Configure VAO/VBO for Texture Quads
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	glGenBuffers(1, &mEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(GLuint), m_Indices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// set The Intital 
	Initialized = true;
}

void TextLabel::Draw()
{
	if (Initialized == false)
	{
		return; // Prevents Calls to the Text Label if its not initialized
	}

	// Enable Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Active corresponding render state
	glUseProgram(m_Program);
	glUniform3fv(glGetUniformLocation(m_Program, "TextColor"), 1, glm::value_ptr(Color));
	glUniformMatrix4fv(glGetUniformLocation(m_Program, "ProjectionMat"), 1, GL_FALSE, glm::value_ptr(camera->ReturnOrthPVM()));
	glUniform1f(glGetUniformLocation(m_Program, "CurrentTime" ), m_CurrentTime);
	glBindVertexArray(mVAO);

	// Store Character Origin that can change as we write each character. Keep the stating text position intact.
	glm::vec2 CharacterOrigin = Position;

	// Iterate through the Texts Characters
	for (std::string::const_iterator TextCharacter = TextStr.begin(); TextCharacter != TextStr.end(); TextCharacter++)
	{
		FontChar FontCharacter = CharacterMap[*TextCharacter];
		GLfloat PosX = CharacterOrigin.x + FontCharacter.Bearing.x * Scale.x;
		GLfloat PosY = CharacterOrigin.y - (FontCharacter.Size.y - FontCharacter.Bearing.y) * Scale.y;
		GLfloat Width = FontCharacter.Size.x * Scale.x;
		GLfloat Height = FontCharacter.Size.y * Scale.y;

		// Update VBO for each character
		GLfloat vertices[4][4] = {
			{PosX, PosY + Height, 0.0, 0.0}, {PosX, PosY, 0.0, 1.0}, 
			{PosX + Width, PosY, 1.0, 1.0}, {PosX + Width, PosY + Height, 1.0, 0.0},
		};

		// Reloadethe vertex aray to the VBO
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

		// Render the Glyph texture over the quad
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, FontCharacter.TextureID);
		glUniform1i(glGetUniformLocation(m_Program, "TextTexture"), 0);
		glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);

		CharacterOrigin.x += FontCharacter.Advance * Scale.x;
	}

	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_BLEND);
}

void TextLabel::Update(float DeltaTime)
{
	m_CurrentTime += DeltaTime;

	// Scale Bounce the Text From the Center
	// Finds the original center, Scales, Finds new center,
	// Finds offset between original and new center, then changes positon based off that
	if (doScaling)
	{
		glm::vec2 OriginalCentre = FindCenterOfText();

		SetScale(glm::vec2(0.4 * sin(m_CurrentTime) + 0.6, 0.4 * sin(m_CurrentTime) + 0.6));

		glm::vec2 ScaledCentre = FindCenterOfText();

		glm::vec2 PositionRatio = ScaledCentre - OriginalCentre;

		SetPosition(glm::vec2 (Position.x - PositionRatio.x, Position.y + PositionRatio.y));
	}
}

glm::vec2 TextLabel::FindCenterOfText()
{
	glm::vec2 CharacterOrigin = Position;
	glm::vec2 TextCentre;
	// Locate Centre of Text
	for (std::string::const_iterator TextCharacter = TextStr.begin(); TextCharacter != TextStr.end(); TextCharacter++)
	{
		FontChar FontCharacter = CharacterMap[*TextCharacter];
		GLfloat PosX = CharacterOrigin.x + FontCharacter.Bearing.x * Scale.x;
		GLfloat PosY = CharacterOrigin.y - (FontCharacter.Size.y - FontCharacter.Bearing.y) * Scale.y;
		GLfloat Width = FontCharacter.Size.x * Scale.x;
		GLfloat Height = FontCharacter.Size.y * Scale.y;

		CharacterOrigin.x += FontCharacter.Advance * Scale.x;

		TextCentre.y = Utils::WindowHeight - (CharacterOrigin.y + (Height / 2));
	}

	TextCentre.x = (Position.x + CharacterOrigin.x) / 2;

	return(glm::vec2(TextCentre.x, TextCentre.y));
}

GLuint TextLabel::GenerateTexture(FT_Face face)
{
	GLuint TextureID;
	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID);

	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RED,
		face->glyph->bitmap.width,
		face->glyph->bitmap.rows,
		0,
		GL_RED,
		GL_UNSIGNED_BYTE,
		face->glyph->bitmap.buffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return TextureID;
}
