#include "Camera.h"

Camera::Camera() {

}

Camera::Camera(glm::vec3 _lookfrom, glm::vec3 _lookat, glm::vec3 _upvec, float _fovy) {
	this->camera_position = _lookfrom;
	this->target_position = _lookat;
	this->up_vector = _upvec;
	this->fov_y = _fovy;
	this->w = glm::normalize(this->camera_position - this->target_position);
	this->u = glm::normalize(glm::cross(this->up_vector, this->w));
	this->v = glm::normalize(glm::cross(this->w, this->u));
}

glm::vec3 Camera::getCameraPos() {
	return this->camera_position;
}

glm::vec3 Camera::getTargetPos() {
	return this->target_position;
}

glm::vec3 Camera::getUpVector() {
	return this->up_vector;
}

glm::vec3 Camera::getDirection() {
	return glm::normalize(this->target_position - this->camera_position);
}

float Camera::getFovY() {
	return this->fov_y;
}

float Camera::getFovX(int _w,int _h) {
	return glm::tan(this->fov_y / 2)*_w / _h;
}

glm::vec3 Camera::getU() {
	return this->u;
}

glm::vec3 Camera::getV() {
	return this->v;
}

glm::vec3 Camera::getW() {
	return this->w;
}



