#include "stdafx.h"
#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &id);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &id);
}

void VertexArray::addBuffer(const VertexBuffer & vbo, const VertexBufferLayout & layout)
{
	bind();
	vbo.bind();

	const auto& elements = layout.getElements();
	for (unsigned int i =0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		unsigned int offset = 0;
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), 
			(const void*) offset);
		offset += element.count * VertexBufferElement::getSizeofType(element.type);
	}
}

void VertexArray::addBuffer(const VertexBuffer & vbo, const unsigned int attributeNumber, const unsigned int coordinateCount)
{
	bind();
	vbo.bind();
	glEnableVertexAttribArray(attributeNumber);
	glVertexAttribPointer(attributeNumber, coordinateCount, GL_FLOAT, false, 0, 0);	
}

void VertexArray::bind() const
{
	glBindVertexArray(id);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}

