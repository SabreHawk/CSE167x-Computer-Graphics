// Transform.cpp: implementation of the Transform class.

#include "Transform.h"

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
	float radians = degrees * pi / 180;
	mat3 tmp_mat_0 = mat3(
		axis.x*axis.x, axis.x*axis.y, axis.x*axis.z,
		axis.x*axis.y, axis.y*axis.y, axis.y*axis.z,
		axis.x*axis.z, axis.y*axis.z, axis.z*axis.z
	);
	mat3 tmp_mat_1 = mat3(
		0, axis.z, -axis.y,
		-axis.z, 0, axis.x,
		axis.y, -axis.x, 0
	);
	mat3 rotate_mat = glm::cos(radians)*mat3(1) + (1 - glm::cos(radians))*tmp_mat_0 + glm::sin(radians)*tmp_mat_1;
	return rotate_mat;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
	// YOUR CODE FOR HW1 HERE
	eye = Transform::rotate(degrees, glm::normalize(up)) * eye;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
	// YOUR CODE FOR HW1 HERE 
	vec3 rotate_axis = glm::cross(glm::normalize(up),glm::normalize(eye));
	mat3 rotate_mat = Transform::rotate(-degrees, rotate_axis);
	eye = rotate_mat * eye;
	up = rotate_mat * up;
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
	// YOUR CODE FOR HW1 HERE
	mat4 translation_mat = mat4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-eye.x, -eye.y, -eye.z, 1
	);
	vec3 w = glm::normalize(eye);
	vec3 u = glm::normalize(glm::cross(up, eye));
	vec3 v = glm::normalize(glm::cross(w, u));
	mat4 rotate_mat = mat4(
		u.x, v.x, w.x, 0,
		u.y, v.y, w.y, 0,
		u.z, v.z, w.z, 0,
		0, 0, 0, 1);
	// You will change this return call
	return rotate_mat * translation_mat;
}

Transform::Transform() {

}

Transform::~Transform() {

}