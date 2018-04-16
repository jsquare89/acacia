#include "stdafx.h"
#include "Shader.h"
#include "Errors.h"

#include <vector>
#include <fstream>


Shader::Shader(const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename) :
	numAttributes(0), id(0), vertexShaderId(0), fragmentShaderId(0)
{
	shaderName = vertexShaderFilename;
	createShader(getFilePath(vertexShaderFilename),getFilePath(fragmentShaderFilename));
}

Shader::~Shader()
{
}

void Shader::createShader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
{
	id = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShaderPath);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShaderPath);

	glAttachShader(id, vs);
	glAttachShader(id, fs);
	glLinkProgram(id);
	glValidateProgram(id);

	glDeleteShader(vs);
	glDeleteShader(fs);
}

std::string Shader::getFilePath(const std::string& filename)
{
	std::string filePath = "res/shaders/";
	return filePath + filename;
}

unsigned int Shader::compileShader(unsigned int type, const std::string& filePath)
{
	unsigned int id = glCreateShader(type);
	std::string shaderSource = parseShader(filePath);
	const char* source = shaderSource.c_str();
	glShaderSource(id, 1, &source, nullptr);
	glCompileShader(id);

	checkShaderCompiled(id, filePath);
	return id;
}

std::string Shader::parseShader(const std::string &filePath)
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
	return fileContents;
}

void Shader::checkShaderCompiled(const unsigned int &id, const std::string &filePath)
{
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
		std::cout << "Shader: " << filePath << " failed to compile. Please check file for errors" << std::endl;
	}
}

GLint Shader::getUniformLocation(const std::string &name)
{
	if (uniformLocationCache.find(name) != uniformLocationCache.end())
		return uniformLocationCache[name];

	GLint location = glGetUniformLocation(id, name.c_str());
	if (location == GL_INVALID_INDEX) 
	{
		std::cout << "Uniform: " << name << " not found in shader " << shaderName << std::endl;
	}
	
	uniformLocationCache[name] = location;
	return location;
}

void Shader::setUniform1i(const std::string & name, int value)
{
	glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform1f(const std::string &name, float value)
{
	glUniform1f(getUniformLocation(name), value);
}

void Shader::setUniform3f(const std::string &name, glm::vec3 vec)
{
	glUniform3f(getUniformLocation(name), vec.x,vec.y,vec.z);
}

void Shader::setUniform4f(const std::string &name, glm::vec4 vec)
{
	glUniform4f(getUniformLocation(name), vec.x, vec.y, vec.z, vec.w);
}

void Shader::setUniformMatrix4(const std::string &name, glm::mat4 mat)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::bind() const
{
	glUseProgram(id);
	//for (int i = 0; i < numAttributes; i++)
	//{
	//	glEnableVertexAttribArray(i);
	//}
}
void Shader::unbind() const
{
	glUseProgram(0);
	//for (int i = 0; i < numAttributes; i++)
	//{
	//	glDisableVertexAttribArray(i);
	//}
}

GLuint Shader::getId()
{
	return id;
}

////////////////////////////////////////////
// TODO: Remove old code no longer in use //
////////////////////////////////////////////
// compileShader, compile, link
void Shader::compileShader(const std::string& filePath, GLuint& id)
{
	const char* contentsPtr = parseShader(filePath).c_str();
	glShaderSource(id, 1, &contentsPtr, nullptr);
	glCompileShader(id);
	checkShaderCompiled(id, filePath);
}

void Shader::compile(const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename)
{
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

	compileShader(getFilePath(vertexShaderFilename), vertexShaderId);
	compileShader(getFilePath(fragmentShaderFilename), fragmentShaderId);
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