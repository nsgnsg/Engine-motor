#include "Emitter.h"


Emitter::Emitter(const Material & mat, bool autofade) : material(mat), autofade(autofade), isEmit(true)
{
}

void Emitter::setRateRange(float min, float max)
{
	
		rateRange.first = min;
		rateRange.second = max;
	
}

void Emitter::setVelocityRange(const glm::vec3 & min, const glm::vec3 & max)
{
	
		velocityRange.first = min;
		velocityRange.second = max;
	
}

void Emitter::setSpinVelocityRange(float min, float max)
{
	
		spinRange.first = min;
		spinRange.second = max;
	
}

void Emitter::setScaleRange(float min, float max)
{
	
		scaleRange.first = min;
		scaleRange.second = max;
	
}

void Emitter::setLifetimeRange(float min, float max)
{
	
		lifeRange.first = min;
		lifeRange.second = max;
	
}

void Emitter::setColorRange(const glm::vec4 & min, const glm::vec4 & max)
{
	
	colorRange.first = min;
	colorRange.second = max;
	
	
}

void Emitter::emit(bool enable)
{
	Emitter::isEmit = enable;
}

bool Emitter::isEmitting()
{
	return Emitter::isEmit;
}

void Emitter::update(float deltaTime)
{
	
	auto  length = Emitter::particles.size();
	for (int i = static_cast<int>(length) - 1; i > 0 ; --i) {
		particles.at(i).update(deltaTime);
		if (particles.at(i).getRemainingLifetime() <= 0) {
			
			particles.erase(particles.begin() + i);
		}
	}
	

	
	if (isEmit) {
		float rate = glm::linearRand(rateRange.first, rateRange.second) * deltaTime + residuo;
		int entero = (int)rate;
		residuo = rate - entero;

		for (int i = 0; i < entero; i++) {
			glm::vec3 randomVel = glm::vec3(glm::linearRand(velocityRange.first.x, velocityRange.second.x),
				glm::linearRand(velocityRange.first.y, velocityRange.second.y),
				glm::linearRand(velocityRange.first.z, velocityRange.second.z));
			
			glm::vec4 randomColor = glm::vec4(glm::linearRand(colorRange.first.x, colorRange.second.x),
				glm::linearRand(colorRange.first.y, colorRange.second.y),
				glm::linearRand(colorRange.first.z, colorRange.second.z),
				glm::linearRand(colorRange.first.t, colorRange.second.t));

			material.setColor(randomColor);
			
			Particle particle = Particle(material, randomVel, glm::linearRand(spinRange.first, spinRange.second),
				glm::linearRand(lifeRange.first, lifeRange.second), autofade);
			particle.setPosition(position);

			float scaleParticle = glm::linearRand(scaleRange.first, scaleRange.second);
			particle.setScale(glm::vec3(scaleParticle, scaleParticle, 1));

			particles.push_back(particle);
		}

		
	}
}

void Emitter::draw()
{
	for (Particle p : particles) {
		p.draw();
	}
}
