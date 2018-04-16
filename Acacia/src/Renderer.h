#pragma once

#include "Shader.h"
#include "Entity.h"
#include "Mesh.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "GL/glew.h"

// Credit : Yan Chernikov - TheChernoProject - OpenGL Error Handling
// https://youtu.be/FBbPWSOQ0-w
// ASSERT(), GLCall(), GLClearError(), GLLogCall()
//#define ASSERT(x) if (!(x)) __debugbreak();
//#define GLCall(x) GLClearError();\
//	x;\
//	ASSERT(GLLogCall(#x, __FILE__, __LINE__))
//
//void GLClearError();
//bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
	Renderer();
	~Renderer();


	void prepare() const;
	void render(const Entity& entity, const Shader& shader) const;
	void render(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const;
};

