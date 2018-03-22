#pragma once
#include <GL/glew.h>
#include <vector>
#include "OBJData.h"


struct VBO_Offset {
	GLintptr positions = 0;
	GLintptr normals = 0;
	GLintptr texcoords = 0;
	GLintptr tangents = 0;
};

struct VBO_Size {
	GLsizeiptr positions = 0;
	GLsizeiptr normals = 0;
	GLsizeiptr texcoords = 0;
	GLsizeiptr tangents = 0;
};

struct VBO_Data {
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texcoords;
	std::vector<glm::vec3> tangents;
	std::vector<unsigned int> indices;
};

class VertexBufferObject
{
public:

	void create(GLenum usage);
	void calculateSize();
	void calculateOffset();
	void bindBuffer(const GLenum &usage);
	void destroy();

	void enable() const;
	void disable() const;
	void populateData(const OBJData &objData);

	void debugPrintData();

	VertexBufferObject();
	~VertexBufferObject();

	unsigned int getDataPositionSize();
	
private:
	void enableVertexBufferObject() const;
	void disableVertexBufferObject() const;
	void enableVertexArray() const;
	void disableVertexArray() const;
	
	GLuint id;
	VBO_Offset offset;
	VBO_Size size;
	VBO_Data data;
};


