#pragma once


#include "VertexBufferObject.h"
#include "OBJData.h"

class Mesh
{
public:
	virtual void load(const char *filename);
	virtual void destroy();


	void bind() const;
	void unbind() const;
	unsigned int getVertexCount() const;
	void draw();
	void drawElements();

	Mesh();
	Mesh(const char * filename);
	Mesh& operator = (const Mesh &m);
	~Mesh() { destroy(); }
private:
	VertexBufferObject *VBO;
};

