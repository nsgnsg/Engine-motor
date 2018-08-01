#pragma once
#include "../lib/glew/glew.h"
#include "../lib/glfw3/glfw3.h"
#include "common.h"
#include <vector>
#include "Shader.h"
#include "Vertex.h"
#include "Light.h"


class State {

public:
	static std::shared_ptr<Shader>	defaultShader;
	static glm::mat4 				projectionMatrix;
	static glm::mat4 				viewMatrix;
	static glm::mat4 				modelMatrix;
	static std::vector<std::shared_ptr<Light>>	lights;
	static glm::vec3						    ambient;

};