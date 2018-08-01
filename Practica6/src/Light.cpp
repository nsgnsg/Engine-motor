#include "Light.h"
#include "State.h"
#include <sstream>
#include <iostream>

Light::Light(Type tipo) : tipo(tipo), color(glm::vec3(1, 1, 1)), linearAtt(0)
{
}

Light::~Light()
{
}

Type Light::getType() const
{
	return Light::tipo;
}

void Light::setType(Type type)
{
	Light::tipo = type;
}

const glm::vec3 & Light::getColor() const
{
	return Light::color;
}

void Light::setColor(const glm::vec3 & color)
{
	Light::color = color;
}

float Light::getLinearAttenuation() const
{
	return Light::linearAtt;
}

void Light::setLinearAttenuation(float att)
{
	Light::linearAtt = att;
}


void Light::prepare(int index, std::shared_ptr<Shader>& shader) const {

	


	std::stringstream isDirStr;
	isDirStr << "isDirectional[" << index << "]";

	
	uint32_t locIsDir = shader->getLocation(isDirStr.str().c_str());

	if (tipo == DIRECTIONAL) {

		shader->setInt(locIsDir, true);
		

	

	}
	else {
		shader->setInt(locIsDir, false);

		std::stringstream linearAttStr;
		linearAttStr << "linearAtt[" << index << "]";
		
		uint32_t locLinearAtt = shader->getLocation(linearAttStr.str().c_str());
		shader->setFloat(locLinearAtt, Light::linearAtt);
		
	}
	
	std::stringstream posLightStr;
	posLightStr << "posLight[" << index << "]";

	uint32_t locPosLight = shader->getLocation(posLightStr.str().c_str());

	glm::vec4 posLight  = State::viewMatrix * glm::scale(glm::rotate(glm::translate(glm::mat4(), position), glm::angle(rotation), glm::axis(rotation)), escale) * glm::vec4(1, 1, 1, 1);


	shader->setVec4(locPosLight, posLight);
	
	std::stringstream lColorStr;
	lColorStr << "colorLight[" << index << "]";

	
	uint32_t locLColor = shader->getLocation(lColorStr.str().c_str());
	shader->setVec3(locLColor, Light::color);



}