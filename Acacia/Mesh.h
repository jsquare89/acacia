#pragma once


#include "VertexBufferObject.h"
#include "OBJData.h"

class Mesh
{
public:
	virtual void load(const char *filename);
	virtual void destroy();

	void draw();

	Mesh();
	~Mesh() { destroy(); }
private:

	VertexBufferObject *VBO;
};

