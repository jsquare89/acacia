#include "stdafx.h"
#include "Mesh.h"
#include "OBJParser.h"
#include <sstream>
#include <fstream>

Mesh::Mesh()
{
	VBO = NULL;
}

Mesh::Mesh(const char * filename)
{
	VBO = NULL;
	load(filename);
}

Mesh& Mesh::operator = (const Mesh &m)
{
	VBO = m.VBO;
	return *this;
}

void Mesh::load(const char * filename)
{
	std::cout << "Loading mesh " << std::string(filename) << std::endl;
	VBO = new VertexBufferObject();

	
	// TODO: isObjFile()
	

	*VBO = OBJParser().getVBODatafromOBJ(filename);
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

void Mesh::drawElements()
{
	VBO->enable();
	glDrawElements(GL_TRIANGLES, VBO->getDataPositionSize(), GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, VBO->getDataPositionSize());
	VBO->disable();
}

void Mesh::bind() const
{
	//VBO->enable();
	
}

void Mesh::unbind() const
{
	VBO->disable();
}

unsigned int Mesh::getVertexCount() const
{
	return VBO->getDataPositionSize();
}