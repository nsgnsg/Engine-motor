

#include "Buffer.h"


using namespace std;


Buffer::Buffer(const vector<Vertex> &vertex, const vector<uint32_t> &index) : vertex(vertex), index(index)
{
	//Buffer ::buffers[2];
	glGenBuffers(2, buffers);
	if (buffers[0] == 0 || buffers[1] == 0) {

		return;
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertex.size(), vertex.data(), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(uint32_t), index.data(), GL_STATIC_DRAW);



}

Buffer::~Buffer() {
	glDeleteBuffers(2, buffers);
}

void Buffer::destroy() {

	glDeleteBuffers(2, Buffer::buffers);
}


void Buffer::draw(const Shader & shader) const
{
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);

	

	shader.setupAttribs();

	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(index.size()), GL_UNSIGNED_INT, nullptr);

}
