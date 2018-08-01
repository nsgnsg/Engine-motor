#pragma once


#include "Billboard.h"



class Particle : public Billboard {
private:
	glm::vec3 vel;
	float remainingLifetime, totalLifetime;
	bool autofade;
public:
	Particle(const Material& mat, const glm::vec3& vel, float spinVel, float lifetime, bool autofade);
	float getRemainingLifetime() const;
	virtual void update(float deltaTime) override;
};