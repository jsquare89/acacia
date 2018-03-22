#include "stdafx.h"
#include "Entity.h"

Entity::Entity(Mesh *mesh, glm::vec3 position, glm::vec3 rotation, float scale)
{
	this->mesh = mesh;
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

Entity::~Entity()
{

}

void Entity::setPosition(glm::vec3 pos)
{
	position = pos;
}

void Entity::setRotation(glm::vec3 rot)
{
	rotation = rot;

}

Mesh * Entity::getMesh() const
{
	return mesh;
}

glm::mat4 Entity::getTransformMatrix()
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	return model;
}


