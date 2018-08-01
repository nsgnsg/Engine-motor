#include "Model.h"


using namespace glm;

Model::Model(const std::shared_ptr<Mesh>& mesh): mesh(mesh)
{
}



void Model::draw()
{
	mat4 mTranslation = translate(mat4(1.0f), position);
	mat4 mRotation = rotate(mTranslation, angle(rotation),axis(rotation));
	State::modelMatrix = scale(mRotation,escale);
	
	Model::mesh->draw();
	
}

void Model::update(float deltaTime) {
	//rotation = rotate(rotation, glm::radians(32.0f *deltaTime), glm::vec3(0, 1, 0));

}
