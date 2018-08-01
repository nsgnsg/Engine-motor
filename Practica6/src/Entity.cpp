#include "Entity.h"

Entity::Entity() : escale(glm::vec3(1, 1, 1))
{
	
}

const glm::vec3 & Entity::getPosition() const
{
	return position;
}

void Entity::setPosition(const glm::vec3 & pos)
{
	Entity::position = pos;
}

const glm::quat & Entity::getRotation() const
{
	return rotation;
}

const void Entity::setRotation(const glm::quat & rot)
{
	Entity::rotation = rot;
}

const glm::vec3 & Entity::getScale() const
{
	return escale;
}

void Entity::setScale(const glm::vec3 & scale)
{
	Entity::escale = scale;
}

void Entity::move(const glm::vec3 & vec)
{
	position += rotation * vec;
}
