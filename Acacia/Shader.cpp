#include "stdafx.h"
#include "Shader.h"
#include "Errors.h"

#include <vector>
#include <fstream>

#include <SOIL\SOIL.h>

Shader::Shader() : numAttributes(0), id(0), vertexShaderId(0), fragmentShaderId(0)
{

}


Shader::~Shader()
{
}

void Shader::compile(const std::string& vertexShaderFileName, const std::string& fragmentShaderFileName)
{
	std::string filePath = "res/shaders/";
	std::string vertexShaderFilePath = filePath + vertexShaderFileName;
	std::string fragmentShaderFilePath = filePath + fragmentShaderFileName;

	//Get a program object.
	id = glCreateProgram();

	vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	if (vertexShaderId == 0)
	{
		fatalError("Vertex Shader failed to be created!");
	}

	fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	if (fragmentShaderId == 0)
	{
		fatalError("Fragment Shader failed to be created!");
	}

	compileShader(vertexShaderFilePath, vertexShaderId);
	compileShader(fragmentShaderFilePath, fragmentShaderId);
}

void Shader::link()
{
	glAttachShader(id, vertexShaderId);
	glAttachShader(id, fragmentShaderId);

	glLinkProgram(id);

	GLint isLinked = 0;
	glGetProgramiv(id, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		glDeleteProgram(id);
		glDeleteShader(vertexShaderId);
		glDeleteShader(fragmentShaderId);

		std::printf("%s\n", &(errorLog[0]));
		fatalError("Shaders failed to link");
	}

	glDetachShader(id, vertexShaderId);
	glDetachShader(id, fragmentShaderId);
	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
}

void Shader::addAttribute(const std::string& attributeName)
{
	glBindAttribLocation(id, numAttributes++, attributeName.c_str());
}

GLuint Shader::getUniformLocation(const std::string uniformName)
{
	GLuint location = glGetUniformLocation(id, uniformName.c_str());
	if (location == GL_INVALID_INDEX) {
		fatalError("Uniform " + uniformName + " not found in shader!");
	}
	return location;
}

void Shader::setUniform1f(GLuint location, float value)
{
	glUniform1f(location, value);
}

void Shader::setUniform3f(GLuint location, glm::vec3 vec)
{
	glUniform3f(location, vec.x,vec.y,vec.z);
	
}

void Shader::setUniformMatrix4(GLuint location, glm::mat4 mat)
{
	glUniformMatrix4fv(location, sizeof(glm::mat4), GL_FALSE, glm::value_ptr(mat));
}

GLuint Shader::getId()
{
	return id;
}

void Shader::use() const
{
	glUseProgram(id);
	for (int i = 0; i < numAttributes; i++)
	{
		glEnableVertexAttribArray(i);
	}
}
void Shader::unuse() const
{
	glUseProgram(0);
	for (int i = 0; i < numAttributes; i++)
	{
		glDisableVertexAttribArray(i);
	}
}

void Shader::compileShader(const std::string& filePath, GLuint& id)
{
	std::ifstream stream(filePath);
	if (stream.fail())
	{
		perror(filePath.c_str());
		fatalError("Failed to open " + filePath);
	}

	std::string fileContents = "";
	std::string line;
	while (std::getline(stream, line))
	{
		fileContents += line + "\n";
	}

	stream.close();

	const char* contentsPtr = fileContents.c_str();
	glShaderSource(id, 1, &contentsPtr, nullptr);

	glCompileShader(id);

	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		glDeleteShader(id);

		std::printf("%s\n", &(errorLog[0]));
		fatalError("Shader" + filePath + " failed to compile");
	}
}
