#include "stdafx.h"
#include "Renderer.h"


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
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void Renderer::render(const Entity& entity, const Shader& shader) const
{
	shader.use();
	// bind vertext array
	// bind index buffer
	// bind textures?

	Mesh* mesh = entity.getMesh();
	mesh->bind();
	glDrawElements(GL_TRIANGLES, mesh->getVertexCount(), GL_UNSIGNED_INT, nullptr);
	
	// may not have to do unbinding - requires testing
	mesh->unbind();
	shader.unuse();
}
