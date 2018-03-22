#pragma once

#include <GL/glew.h>
#include <string>


class Shader
{
public:
	void compile(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
	void link();
	
	void setUniform1f(GLuint location, float value);
	void setUniform3f(GLuint location, glm::vec3 vec);
	void setUniformMatrix4(GLuint location, glm::mat4 mat);
	void addAttribute(const std::string& attributeName);
	GLuint getUniformLocation(const std::string uniformName);
	GLuint getId();
	void use() const;
	void unuse() const;

	Shader();
	~Shader();

private:
	void compileShader(const std::string& filePath, GLuint& id);

	int numAttributes;
	GLuint id;
	GLuint vertexShaderId;
	GLuint fragmentShaderId;
};

