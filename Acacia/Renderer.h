#pragma once

#include "Shader.h"
#include "Entity.h"
#include "Mesh.h"

class Renderer
{
public:
	Renderer();
	~Renderer();


	void prepare() const;
	void render(const Entity& entity, const Shader& shader) const;

};

