#include "Billboard.h"

vector<Vertex> calculateVertex() {

	glm::vec3 leftDownVertex, leftUpVertex, rightDownVertex, rightUpVertex;

	leftDownVertex.x =  - 0.5f;
	leftUpVertex.x =  - 0.5f;
	rightDownVertex.x =  0.5f;
	rightUpVertex.x =  0.5f;

	leftDownVertex.y = - 0.5f;
	leftUpVertex.y = 0.5f;
	rightDownVertex.y =  - 0.5f;
	rightUpVertex.y =  0.5f;

	leftDownVertex.z = 0;
	leftUpVertex.z = 0;
	rightDownVertex.z = 0;
	rightUpVertex.z = 0;

	vector<Vertex> billboardVertex;
	billboardVertex.push_back(Vertex(leftDownVertex, glm::vec2(0, 0), glm::vec3(0,0,1)));
	billboardVertex.push_back(Vertex(rightDownVertex, glm::vec2(1, 0), glm::vec3(0, 0, 1)));
	billboardVertex.push_back(Vertex(rightUpVertex, glm::vec2(1, 1), glm::vec3(0, 0, 1)));
	billboardVertex.push_back(Vertex(leftUpVertex, glm::vec2(0, 1), glm::vec3(0, 0, 1)));

	return billboardVertex;
}


Billboard::Billboard(const Material & mat) : material(mat), size(1,1), spin(0)
{
	if (mat.getTexture()) {
		Billboard::size = mat.getTexture()->getSize();
	}
	
	material.setDepthWrite(false);

	std::vector<Vertex> vertex = calculateVertex();
	std::vector<uint32_t> index = { 0,1,2,0,2,3 };
	Billboard::buffer = make_shared<Buffer>(vertex, index);
	
}

Billboard::~Billboard()
{
}



const Material & Billboard::getMaterial() const
{
	return Billboard::material;
}

Material & Billboard::getMaterial()
{
	return Billboard::material;
}

const glm::vec2 & Billboard::getSize() const
{
	return Billboard::size;
}

void Billboard::setSize(const glm::vec2 & size)
{
	Billboard::size = size;
	
}

float Billboard::getSpin() const
{
	return Billboard::spin;
}

void Billboard::setSpin(float spin)
{
	Billboard::spin = spin;
}

void Billboard::draw()
{
	
	

	glm::mat4 model = glm::transpose(State::viewMatrix);
	model[0][3] = 0;
	model[1][3] = 0;
	model[2][3] = 0;
	model[3]= glm::vec4(getPosition(),1);
	

	

	//glm::mat4 aux1 = glm::make_mat4(modelArray);
	model = glm::rotate(model,glm::radians(spin),glm::vec3(0,0,1));
	glm::vec3 billboardScale = glm::vec3(size, 1) * escale;
	State::modelMatrix = glm::scale(model, billboardScale);
	
	Billboard::material.prepare();

	buffer->draw(*(material.getShader()));
}
