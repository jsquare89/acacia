#include "stdafx.h"
#include "Texture.h"
#include <assert.h>

Texture::Texture()
{
	id = 0;
}

void Texture::loadTexture2d(const char *filename)
{
	load(filename, GL_TEXTURE_2D);
}

void Texture::loadTextureCubeMap(const char *filename)
{
	load(filename, GL_TEXTURE_CUBE_MAP);
}

void Texture::load(const char *filename, GLenum textureType)
{
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
	unsigned char* image = SOIL_load_image(getFilePath(filename).c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	loadData(textureType, width, height, image);
	setTextureParameters(textureType);
	unbind();

	SOIL_free_image_data(image);
	printf("Loaded image\n");
}

std::string Texture::getFilePath(const char* filename)
{
	std::string filePath = "res/textures/";
	filePath.append(filename);
	filePath.append(".jpg");
	return filePath;
}
void Texture::setTextureParameters(const GLenum &textureType)
{
	glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glGenerateMipmap(textureType);
}

void Texture::gen()
{
	destroy();
	glGenTextures(1, &id);
}


void Texture::loadData(GLenum textureType, int width, int height, unsigned char * image)
{
	if(textureType == GL_TEXTURE_2D)
		glTexImage2D(textureType, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	if (textureType == GL_TEXTURE_CUBE_MAP)
	{
		
	}
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, id); 
}

void Texture::bind(GLuint slot) const
{
	assert(slot >= 0 && slot <= 31);

	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0); 
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