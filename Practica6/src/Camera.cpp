#include "Camera.h"


using namespace glm;



Camera::Camera(const glm::ivec2 & viewportSize): viewport(0, 0, viewportSize.x, viewportSize.y), clearColor(0,0,0) {
		projection = glm::perspective<float>(glm::radians(60.0f), viewportSize.y == 0 ? 1 : static_cast<float>(viewportSize.x) / viewportSize.y, 1, 1000);
}


const glm::mat4 & Camera::getProjection() const
{
	return Camera::projection;
}

void Camera::setProjection(const glm::mat4 & proj)
{
	projection = proj;
}

const glm::ivec4 & Camera::getViewport() const
{
	return Camera::viewport;
}

void Camera::setViewport(const glm::ivec4 & vp)
{
	viewport = vp;
}

const glm::vec3 & Camera::getClearColor() const
{
	return Camera::clearColor;
}

void Camera::setClearColor(const glm::vec3 & color)
{
	clearColor = color;
}

void Camera::prepare()
{
	State::projectionMatrix = projection;

	mat4 mRotation = rotate(mat4(), -angle(rotation), axis(rotation));
	State::viewMatrix = translate(mRotation, -position);

	glDepthMask(GL_TRUE);


	glViewport(viewport.x, viewport.y, viewport.z, viewport.w);
	glScissor(viewport.x, viewport.y, viewport.z, viewport.w);
	glClearColor(clearColor.x, clearColor.y, clearColor.z, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
}
