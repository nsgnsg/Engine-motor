
#pragma once
#include "../lib/glew/glew.h"
#include "../lib/glfw3/glfw3.h"
#include "common.h"
#include <vector>
#include "Shader.h"
#include "Vertex.h"


class Entity {
protected:
	glm::vec3 position, escale;
	glm::quat rotation;
public:
	Entity();
	virtual ~Entity() {}

	const glm::vec3&	getPosition() const;
	void			setPosition(const glm::vec3& pos);
	const			glm::quat& getRotation() const;	// puede ser quat
	const void		setRotation(const glm::quat& rot);	// puede ser quat
	const glm::vec3&	getScale() const;
	void			setScale(const glm::vec3& scale);

	void			move(const glm::vec3& vec);	// Ver en las diapositivas

	virtual void	update(float deltaTime) {}
	virtual void	draw() {}

};
