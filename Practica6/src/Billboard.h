#pragma once

#include "Entity.h"
#include "Shader.h"
#include "Material.h"
#include "Buffer.h"



class Billboard : public Entity {
protected:
	Material material;
	shared_ptr<Buffer> buffer;
	glm::vec2 size;
	float spin;
	glm::vec3 velocity;
public:
	Billboard(const Material& mat);
	~Billboard();
	const Material& getMaterial() const;
	Material& getMaterial();
	const glm::vec2& getSize() const;
	void setSize(const glm::vec2& size);
	float getSpin() const;
	void setSpin(float spin);
	virtual void draw() override;
	
};