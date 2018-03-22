#pragma once

#include <GL/glew.h>
#include <SOIL\SOIL.h>

class Texture
{
public:
	virtual void load(const char *fileName, GLenum textureType);
	virtual void destroy();

	GLuint getId() const { return id; }

	void bind(GLuint slot) const;
	void unbind(GLuint slot) const;	
	
	Texture();
	~Texture();
private:
	void gen();
	void setTextureParameters(const GLenum &textureType);
	void loadData(GLenum target, int width, int height, unsigned char * image);
	void bind();
	void unbind();

	void loadTextureCubeMap(const char *filename);
	void loadTexture2d(const char *filename);

	GLuint id;
	static bool generateMipmap;
};

