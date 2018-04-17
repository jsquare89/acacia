#include "stdafx.h"
#include "Renderer.h"

//void GLClearError()
//{
//	while (glGetError() != GL_NO_ERROR);
//}
//
//bool GLLogCall(const char* function, const char* file, int line)
//{
//	while (GLenum error = glGetError())
//	{
//		std::cout << "[OpenGL Error] (" << error << "): " << function <<
//			" " << file << ":" << line << std::endl;
//		return false;
//	}
//	return false;
//}

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::prepare() const
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
}

void Renderer::render(const Entity& entity, const Shader& shader) const
{
	shader.bind();
	// bind vertext array
	// bind index buffer
	// bind textures?

	Mesh mesh = entity.getMesh();
	mesh.bind();
	mesh.drawElements();
	//glDrawElements(GL_TRIANGLES, mesh->getVertexCount(), GL_UNSIGNED_INT, nullptr);
	
	// may not have to do unbinding - requires testing
	mesh.unbind();
	shader.unbind();
}

void Renderer::render(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const
{
	shader.bind();
	vao.bind();
	//ibo.bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	//glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, nullptr);
}
