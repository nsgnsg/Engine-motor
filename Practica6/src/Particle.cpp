#include "Particle.h"

Particle::Particle(const Material & mat, const glm::vec3 & vel, float spinVel, float lifetime, bool autofade) : Billboard(mat),
	remainingLifetime(lifetime),totalLifetime(lifetime), autofade(autofade)
{
	Billboard::velocity = vel;
	Billboard::spin = spinVel;
}

float Particle::getRemainingLifetime() const
{
	return Particle::remainingLifetime;
}

void Particle::update(float deltaTime)
{
	Particle::remainingLifetime = glm::max(0.0f, remainingLifetime - deltaTime);

	move(velocity * deltaTime);

	rotation *= glm::quat(glm::radians(glm::vec3(0, 0, spin * deltaTime)));

	if (autofade)
	{
		float opacity = 0.0f;
		if (remainingLifetime > 0)
			opacity = remainingLifetime / totalLifetime;
		
		material.setColor(glm::vec4(material.getColor().x, material.getColor().y, material.getColor().z, opacity));
	}
}
	
