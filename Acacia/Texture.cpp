#include "stdafx.h"
#include "Texture.h"


Texture::Texture()
{
	id = 0;
}

void Texture::load(const char *fileName)
{
	GLenum textureType = GL_TEXTURE_2D;

	gen();
	if (id == 0)
	{
		//handle error
		printf("error loading texture\n");
		return;
	}

	bind();
	//Load, create texture
	int width, height;
	unsigned char* image = SOIL_load_image(fileName, &width, &height, 0, SOIL_LOAD_RGB);
	loadData(textureType, width, height, image);
	setTextureParameters(textureType);
	unbind();

	SOIL_free_image_data(image);
	printf("Loaded image\n");
}

void Texture::setTextureParameters(const GLenum &textureType)
{
	glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(textureType);
}

void Texture::gen()
{
	destroy();
	glGenTextures(1, &id);
}


void Texture::loadData(GLenum textureType, int width, int height, unsigned char * image)
{
	glTexImage2D(textureType, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, id); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
}

void Texture::bind(GLuint slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	//glEnable(getTextureType());
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void Texture::unbind(GLuint slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::destroy()
{
	glDeleteTextures(1, &id);
	id = 0;
}

Texture::~Texture()
{
	destroy();
}
