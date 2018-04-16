#pragma once
#include <vector>
#include <GL\glew.h>


struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned int normalized;

	static unsigned int getSizeofType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;
		}

		//ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
public:
	VertexBufferLayout();
	~VertexBufferLayout();

	inline const std::vector<VertexBufferElement>& getElements() const { return elements; };
	inline unsigned int getStride() const { return stride; }

	template<typename T>
	void push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void push<float>(unsigned int count)
	{
		elements.push_back({ GL_FLOAT, count, GL_FALSE });
		stride += count * VertexBufferElement::getSizeofType(GL_FLOAT);
	}

	template<>
	void push<unsigned int>(unsigned int count)
	{
		elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		stride += count * VertexBufferElement::getSizeofType(GL_UNSIGNED_INT);
	}

private:
	std::vector<VertexBufferElement> elements;
	unsigned int stride;
};

