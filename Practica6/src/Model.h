#pragma once

#include "Entity.h"
#include "Mesh.h"
#include "State.h"


class Model: public Entity {
private:
	std::shared_ptr<Mesh> mesh;
public:
	Model(const std::shared_ptr<Mesh>& mesh); 
	virtual void draw() override;
	
	virtual void	update(float deltaTime) override;
	

};
