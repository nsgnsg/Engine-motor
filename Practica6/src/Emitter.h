#pragma once

#include "Entity.h"
#include "Material.h"
#include "Particle.h"
#include <iostream>



class Emitter : public Entity {
protected:
	Material material;
	bool autofade;
	bool isEmit;
	std::pair<float, float> rateRange, spinRange, scaleRange, lifeRange ;
	std::pair<glm::vec3, glm::vec3> velocityRange, colorRange;
	float residuo;
	std::vector<Particle> particles;

public:
	Emitter(const Material& mat, bool autofade = true);
	void setRateRange(float min, float max);
	void setVelocityRange(const glm::vec3& min, const glm::vec3& max);
	void setSpinVelocityRange(float min, float max);
	void setScaleRange(float min, float max);
	void setLifetimeRange(float min, float max);
	void setColorRange(const glm::vec4& min, const glm::vec4& max);
	void emit(bool enable);
	bool isEmitting();
	virtual void update(float deltaTime) override;
	virtual void draw() override;


};