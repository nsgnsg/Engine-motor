#pragma once
#include "../lib/glew/glew.h"
#include "../lib/glfw3/glfw3.h"
#include "common.h"
#include <vector>
#include "Shader.h"
#include "Vertex.h"


using namespace std;

class Buffer {

private:
	uint32_t buffers[2];
	size_t numIndex;
	vector<Vertex> vertex;
	vector<uint32_t> index;

public:
	
	Buffer(const vector<Vertex> &vertex, const vector<uint32_t> &index);
	~Buffer();
	void destroy();
	void draw(const Shader& shader) const;


};