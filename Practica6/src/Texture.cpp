#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Texture::Texture(int width, int height, GLuint texId) : size(width, height), texId(texId){}

Texture::~Texture() {
	if (Texture::texId != 0) {
		glDeleteTextures(1, &texId);
	}
}

std::shared_ptr<Texture> Texture::load(const char * filename)
{
	
	int height, width;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* image = stbi_load(filename, &width, &height, nullptr, 4);

	//if the image load wrong, return nullptr
	if (image == nullptr) {
		return nullptr;
	}
	//Step 1: Generate texture 
	GLuint texId;
	glGenTextures(1, &texId);

	
	
	//Step 2: Bind texture
	glBindTexture(GL_TEXTURE_2D, texId);
	
	
	//Step 3: Stablish parametres
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	
	//Step 4: Load image
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	
	//Step 5: Generate mipmap
	glGenerateMipmap(GL_TEXTURE_2D);

	
	//Free image
	stbi_image_free(image);


	return std::shared_ptr<Texture> (new Texture(width, height, texId), [](Texture* t) { delete t; });
}

uint32_t Texture::getId() const
{
	return texId;
}

const glm::ivec2 & Texture::getSize() const
{
	return size;
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, texId);
}
