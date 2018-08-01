#include "Material.h"


Material::Material(const std::shared_ptr<Texture>& tex, const std::shared_ptr<Shader>& shader) : tex(tex), shader(shader), blendMode(BlendMode::ALPHA),
depthWrite(true), culling(true), lighting(true), color(glm::vec4(1,1,1,1)) {

}

const std::shared_ptr<Shader>& Material::getShader() const
{
	return Material::shader == nullptr ? State::defaultShader : Material::shader;
}

std::shared_ptr<Shader>& Material::getShader()
{
	return Material::shader == nullptr ? State::defaultShader : Material::shader;
}

void Material::setShader(const std::shared_ptr<Shader>& shader)
{
	Material::shader = shader;
}

const std::shared_ptr<Texture>& Material::getTexture() const
{
	return Material::tex;
}

void Material::setTexture(const std::shared_ptr<Texture>& tex)
{
	Material::tex = tex;
}

const glm::vec4 & Material::getColor() const
{
	return Material::color;
}

void Material::setColor(const glm::vec4 & color)
{
	Material::color = color;
}

uint8_t Material::getShininess() const
{
	return Material::shininess;
}

void Material::setShininess(uint8_t shininess)
{
	Material::shininess = shininess;
}

BlendMode Material::getBlendMode() const
{
	return Material::blendMode;
}

void Material::setBlendMode(BlendMode blendMode)
{
	Material::blendMode = blendMode;
}

bool Material::getLighting() const
{
	return Material::lighting;
}

void Material::setLighting(bool enable)
{
	Material::lighting = enable;
}

bool Material::getCulling() const
{
	return Material::culling;
}

void Material::setCulling(bool enable)
{
	Material::culling = enable;
}

bool Material::getDepthWrite() const
{
	return Material::depthWrite;
}

void Material::setDepthWrite(bool enable)
{
	Material::depthWrite = enable;
}

void Material::prepare()
{
	std::shared_ptr<Shader> s = getShader();



	//prepare GL states
	if (blendMode == BlendMode::ALPHA) 
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	else if (blendMode == BlendMode::​MUL​) 
		glBlendFunc(GL_ZERO, GL_SRC_COLOR);
	else  
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	
	


	if (culling) 
		glEnable(GL_CULL_FACE);
	else 
		glDisable(GL_CULL_FACE);


	if (depthWrite)
		glDepthMask(GL_TRUE);
	else
		glDepthMask(GL_FALSE);

	

	//Activate shader
	s->use();

	//write in shaders
	//MVP 
	glm::mat4 model = State::modelMatrix;
	glm::mat4 view = State::viewMatrix;
	glm::mat4 projection = State::projectionMatrix;

	glm::mat4 MVP = projection * view * model;

	//Light Components, MV and normalMat

	glm::mat4 MV = view * model;
	glm::mat4 normalMat = glm::transpose(glm::inverse(MV));

	uint32_t locMVP = s->getLocation("MVP");


	s->setMatrix(locMVP, MVP);


	uint32_t locMV = s->getLocation("MV");
	s->setMatrix(locMV, MV);

	uint32_t locNormalMat = s->getLocation("normalMat");
	s->setMatrix(locNormalMat, normalMat);

	uint32_t locNumLights = s->getLocation("numLights");
	
	if (lighting) {
		s->setInt(locNumLights, 0);
	}
	else {
		s->setInt(locNumLights, State::lights.size());
	}

	

	uint32_t locMaterialColor = s->getLocation("materialColor");
	s->setVec4(locMaterialColor, Material::color);

	uint32_t locShininess = s->getLocation("shininess");
	s->setInt(locShininess, Material::shininess);

	uint32_t locAmbient = s->getLocation("ambient");
	s->setVec3(locAmbient, State::ambient);



	//texSampler
	uint32_t locTS = s->getLocation("texSampler");
	s->setInt(locTS, 0);

	//isTexturized;
	uint32_t locIT = s->getLocation("isTexturized");


	if (tex != nullptr) {
		s->setInt(locIT, true);
		//in the if, we link the texture too
		tex->bind();
	}
	else {
		s->setInt(locIT, false);
	}

	for (int i = 0; i < State::lights.size(); i++) {
		State::lights[i]->prepare(i, s);
	}


}
