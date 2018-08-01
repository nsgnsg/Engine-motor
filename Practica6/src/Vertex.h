#pragma once
#include "common.h"


class Vertex {
	public:
	glm::vec3 pos;
	glm::vec2 uvTex;

	glm::vec3 normal;
	

	Vertex(glm::vec3 pos, glm::vec2 uvTex, glm::vec3 normal = glm::vec3(0, 0, 0));
	

};

