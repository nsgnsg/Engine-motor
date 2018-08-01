#pragma once

#include "Entity.h"
#include "Mesh.h"
#include "State.h"
#include "Camera.h"
#include <vector>
#include "Light.h"


class World  {
private:
	std::vector<std::shared_ptr<Entity>> entities;
	std::vector<std::shared_ptr<Camera>> cameras;
	std::vector<std::shared_ptr<Light>> lights;
	glm::vec3 ambient;
public:
	void addEntity(const std::shared_ptr<Entity>& entity);
	void removeEntity(const std::shared_ptr<Entity>& entity);
	size_t getNumEntities() const;
	const std::shared_ptr<Entity>& getEntity(size_t index) const;
	std::shared_ptr<Entity>& getEntity(size_t index);
	const glm::vec3& getAmbient() const;
	void setAmbient(const glm::vec3& ambient);
	void update(float deltaTime);
	void draw();
	


};
