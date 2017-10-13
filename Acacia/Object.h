#pragma once

#include <GL/glew.h>
#include "GLSLProgram.h"

class Object
{
public:
	Object();
	~Object();

	void init();
	void render();

private:
	GLfloat *_vertices; // vertices for triangle
	GLuint *_indices; // triangle indices
	GLuint VBO, VAO, EBO;
};

