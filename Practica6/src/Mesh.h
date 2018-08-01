#pragma once
#include "../lib/glew/glew.h"
#include "../lib/glfw3/glfw3.h"
#include "pugixml.hpp"
#include "pugiconfig.hpp"
#include "utils.h"
#include "common.h"
#include <vector>
#include "Shader.h"
#include "Buffer.h"
#include "State.h"
#include "Material.h"
#include <iostream>


class Mesh {
private:
	std::vector<std::pair<std::shared_ptr<Buffer>, Material>> buffers;
	//size_t size;
public:
	Mesh();
	/*
	void addBuffer(const std::shared_ptr<Buffer>& buffer,
		const std::shared_ptr<Shader>& shader = nullptr);*/
	void addBuffer(const std::shared_ptr<Buffer>& buffer, const Material& material);
	size_t getNumBuffers() const;
	const std::shared_ptr<Buffer>& getBuffer(size_t index) const;
	std::shared_ptr<Buffer>& getBuffer(size_t index);
	const Material& getMaterial(size_t index) const;
	Material& getMaterial(size_t index);
	static std::shared_ptr<Mesh> load(const char* filename, const std::shared_ptr<Shader>& shader = nullptr);

	void draw();

};