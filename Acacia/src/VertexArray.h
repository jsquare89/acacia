#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void addBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout);
	void addBuffer(const VertexBuffer & vbo, const unsigned int attributeNumber, const unsigned int coordinateCount);

	void bind() const;
	void unbind() const;	
private :
	unsigned int id;
};

