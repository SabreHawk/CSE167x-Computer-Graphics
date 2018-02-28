// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"
#include <iostream>
// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
	float radians = degrees * pi / 180;
	vec3 tmp_axis = glm::normalize(axis);
	mat3 tmp_mat_0 = mat3(
		tmp_axis.x*tmp_axis.x, tmp_axis.x*tmp_axis.y, tmp_axis.x*tmp_axis.z,
		tmp_axis.x*tmp_axis.y, tmp_axis.y*tmp_axis.y, tmp_axis.y*tmp_axis.z,
		tmp_axis.x*tmp_axis.z, tmp_axis.y*tmp_axis.z, tmp_axis.z*tmp_axis.z
	);
	mat3 tmp_mat_1 = mat3(
		0, tmp_axis.z, -tmp_axis.y,
		-tmp_axis.z, 0, tmp_axis.x,
		tmp_axis.y, -tmp_axis.x, 0
	);
	mat3 rotate_mat = glm::cos(radians)*mat3(1) + (1 - glm::cos(radians))*tmp_mat_0 + glm::sin(radians)*tmp_mat_1;
	return rotate_mat;
}

void Transform::left(float degrees, vec3& eye, vec3& up) {
	// YOUR CODE FOR HW2 HERE
	// Likely the same as in HW 1.  
	eye = Transform::rotate(degrees, glm::normalize(up)) * eye;
}

void Transform::up(float degrees, vec3& eye, vec3& up) {
	// YOUR CODE FOR HW2 HERE 
	// Likely the same as in HW 1.
	vec3 rotate_axis = glm::cross(glm::normalize(up), glm::normalize(eye));
	mat3 rotate_mat = Transform::rotate(-degrees, rotate_axis);
	eye = rotate_mat * eye;
	up = rotate_mat * up;
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) {
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

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar) {
	float scale = 1 / glm::tan(fovy * pi / 180 / 2);
	float tmp_v0 = (zNear + zFar) / (zNear - zFar);
	float tmp_v1 = 2 * zNear * zFar / (zNear - zFar);
	mat4 prp_mat = mat4(
		scale / aspect, 0, 0, 0,
		0, scale, 0, 0,
		0, 0, tmp_v0, -1,
		0, 0, tmp_v1, 0
	);
	return prp_mat;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) {
	mat4 scale_mat = mat4(
		sx, 0, 0, 0,
		0, sy, 0, 0,
		0, 0, sz, 0,
		0, 0, 0, 1
	);
	return scale_mat;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) {
	mat4 trans_mat = mat4(
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		tx,ty,tz,1
	);
	return trans_mat;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) {
	vec3 x = glm::cross(up, zvec);
	vec3 y = glm::cross(zvec, x);
	vec3 ret = glm::normalize(y);
	return ret;
}


Transform::Transform() {

}

Transform::~Transform() {

}
