#include "TextureLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


// Default Constructor
TextureLoader::TextureLoader()
{
}

// Default Destructor
TextureLoader::~TextureLoader()
{
}


// Create texture from file directory
GLuint TextureLoader::CreateTexture(const char* TextureFileName)
{
	std::cout << "\n";
	// Ensures images are orientated correctly
	stbi_set_flip_vertically_on_load(true);

	// Creates an iterator to go through the Texture Map.
	std::map <const char*, GLuint>::iterator TextureMapIterator;
	TextureMapIterator = textureMap.find(TextureFileName);
	// If it Finds the texture in the map, Uses that texture instead of creating a new one.
	if (TextureMapIterator != textureMap.end())
	{
		std::cout << "Texture ('" << TextureFileName << "') located in map" << std::endl;
		return (textureMap.find(TextureFileName)->second);
	}
	// Otherwise create a new texture.
	else
	{
		std::cout << "Texture ('" << TextureFileName << "') Created and added to Map" << std::endl;

		// Create Texture Information
		GLuint TextureID;
		int ImageWidth;
		int ImageHeight;
		int ImageComponents;
		// Load image data
		unsigned char* ImageData = stbi_load(TextureFileName, &ImageWidth, &ImageHeight, &ImageComponents, 0);


		// Create and bind new texture template
		glGenTextures(1, &TextureID);
		glBindTexture(GL_TEXTURE_2D, TextureID);

		// Check how many components the loaded images has.
		GLint LoadedComponenets = (ImageComponents == 4) ? GL_RGBA : GL_RGB;

		glTexImage2D(GL_TEXTURE_2D, 0, LoadedComponenets, ImageWidth, ImageHeight, 0, LoadedComponenets, GL_UNSIGNED_BYTE, ImageData);

		// Generate MinMaps
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Unbind Texture
		stbi_image_free(ImageData);
		glBindTexture(GL_TEXTURE_2D, 0);

		// Add Texture to the Map
		textureMap.emplace(TextureFileName, TextureID);

		// Report if there is an error
		if (glGetError() != 0)
		{
			std::cout << "Error Loading Texture: " << TextureFileName << std::endl;
		}

		// Return the Texture ID
		return(TextureID);
	}

	
}
