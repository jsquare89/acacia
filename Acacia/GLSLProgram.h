#pragma once

#include <GL/glew.h>
#include <string>


class GLSLProgram
{
public:
	void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
	void linkShaders();
	void addAttribute(const std::string& attributeName);
	GLuint getUniformLocation(const std::string uniformName);
	GLuint getId();
	void use();
	void unuse();

	GLSLProgram();
	~GLSLProgram();

private:
	void compileShader(const std::string& filePath, GLuint& id);

	int numAttributes;
	GLuint id;
	GLuint vertexShaderId;
	GLuint fragmentShaderId;
};

