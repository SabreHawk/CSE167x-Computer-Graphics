#include "Camera.h"

Camera::Camera() {

}

Camera::Camera(glm::vec3 _lookfrom, glm::vec3 _lookat, glm::vec3 _upvec, float _fovy) {
	this->camera_position = _lookfrom;
	this->target_position = _lookat;
	this->up_vector = _upvec;
	this->fov_y = _fovy;
}