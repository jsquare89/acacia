#include "stdafx.h"
#include "Mesh.h"
#include "OBJParser.h"
#include <sstream>
#include <fstream>

Mesh::Mesh()
{
	VBO = NULL;
}

void Mesh::load(const char * fileName)
{
	std::cout << "Loading mesh " << std::string(fileName) << std::endl;
	VBO = new VertexBufferObject();

	
	// TODO: isObjFile()
	

	*VBO = OBJParser().getVBODatafromOBJ(fileName);
	VBO->create(GL_STATIC_DRAW);
}

void Mesh::destroy()
{
	VBO->destroy();
	delete VBO;
	VBO = NULL;
}

void Mesh::draw()
{
	VBO->enable();
	glDrawArrays(GL_TRIANGLES, 0, VBO->getDataPositionSize());
	VBO->disable();
}

void Mesh::bind() const
{
	VBO->enable();
}

void Mesh::unbind() const
{
	VBO->disable();
}

unsigned int Mesh::getVertexCount() const
{
	return VBO->getDataPositionSize();
}