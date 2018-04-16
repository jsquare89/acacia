#pragma once
#include "Mesh.h"

class Entity
{
public:
	Entity(const Mesh &mesh, const glm::vec3& position, const glm::vec3 &rotation, const float &scale);
	~Entity();

	void setPosition(glm::vec3 pos);
	void setRotation(glm::vec3 rot);

	Mesh getMesh() const;

	glm::mat4 getTransformMatrix();

private:

	Mesh mesh; // model?
	glm::vec3 position;
	glm::vec3 rotation;
	float scale;
};

