#pragma once
#include "../lib/glew/glew.h"
#include "../lib/glfw3/glfw3.h"
#include "common.h"



class Texture {
private:
	glm::ivec2 size;
	GLuint texId;

	Texture(int w, int h, GLuint texId);
	~Texture();

public:
	static std::shared_ptr<Texture>	load(const char* filename);
	uint32_t					    getId() const;
	const glm::ivec2&				getSize() const;
	void						    bind() const;
};