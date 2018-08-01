#pragma once
#include "../lib/glew/glew.h"
#include "../lib/glfw3/glfw3.h"
#include "common.h"
#include "Shader.h"
#include "Texture.h"
#include "State.h"
#include "BlendMode.h"





class Material {
private:
	std::shared_ptr<Texture> tex;
	std::shared_ptr<Shader> shader;
	glm::vec4 color;
	uint8_t shininess;
	BlendMode blendMode;
	bool lighting, culling, depthWrite;

public:
	Material(const std::shared_ptr<Texture>& tex = nullptr, const std::shared_ptr<Shader>& shader = nullptr);
	const std::shared_ptr<Shader>& getShader() const;
	std::shared_ptr<Shader>& getShader();
	void setShader(const std::shared_ptr<Shader>& shader);
	const std::shared_ptr<Texture>& getTexture() const;
	void setTexture(const std::shared_ptr<Texture>& tex);
	const glm::vec4& getColor() const;
	void setColor(const glm::vec4& color);
	uint8_t getShininess() const;
	void setShininess(uint8_t shininess);
	BlendMode getBlendMode() const;
	void setBlendMode(BlendMode blendMode);
	bool getLighting() const;
	void setLighting(bool enable);
	bool getCulling() const;
	void setCulling(bool enable);
	bool getDepthWrite() const;
	void setDepthWrite(bool enable);
	void prepare();


};