#pragma once

#include <GL/glew.h>
#include <string>
#include <unordered_map>

class Shader
{
public:
	Shader(const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename);
	~Shader();

	void createShader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);
	std::string getFilePath(const std::string& filename);
	unsigned int compileShader(unsigned int type, const std::string& filePath);
	std::string Shader::parseShader(const std::string &file);
	void checkShaderCompiled(const unsigned int &id, const std::string &filePath);
	void bind() const;
	void unbind() const;

	GLint getUniformLocation(const std::string &uniformName);
	void setUniform1i(const std::string &name, int value);
	void setUniform1f(const std::string &name, float value);
	void setUniform3f(const std::string &name, glm::vec3 vec);
	void setUniform4f(const std::string &name, glm::vec4 vec);
	void setUniformMatrix4(const std::string &name, glm::mat4 mat);

	// to remove
	GLuint getId();
	void addAttribute(const std::string& attributeName);
	void compile(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
	void link();

private:
	GLuint id;
	std::unordered_map<std::string, int> uniformLocationCache;
	std::string shaderName;
	// to remove
	void compileShader(const std::string& filePath, GLuint& id);
	int numAttributes;
	GLuint vertexShaderId;
	GLuint fragmentShaderId;
};

