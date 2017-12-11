// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
    // YOUR CODE FOR HW2 HERE
    // Please implement this.  Likely the same as in HW 1.  
	mat3 rotate_matrix;
	double  radian = degrees * pi / 180;
	vec3 temp_axis = glm::normalize(axis);
	double cosA = cos(radian);
	double oneC = 1 - cosA;
	double sinA = sin(radian);
	rotate_matrix[0][0] = temp_axis.x * temp_axis.x * oneC + cosA;
	rotate_matrix[1][0] = temp_axis.x * temp_axis.y * oneC - temp_axis.z * sinA;
	rotate_matrix[2][0] = temp_axis.x * temp_axis.z * oneC + temp_axis.y * sinA;
	rotate_matrix[0][1] = temp_axis.y * temp_axis.x * oneC + temp_axis.z * sinA;
	rotate_matrix[1][1] = temp_axis.y * temp_axis.y * oneC + cosA;
	rotate_matrix[2][1] = temp_axis.y * temp_axis.z * oneC - temp_axis.x * sinA;
	rotate_matrix[0][2] = temp_axis.z * temp_axis.x * oneC - temp_axis.y * sinA;
	rotate_matrix[1][2] = temp_axis.z * temp_axis.y * oneC + temp_axis.x * sinA;
	rotate_matrix[2][2] = temp_axis.z * temp_axis.z * oneC + cosA;
	
    return rotate_matrix;
}

void Transform::left(float degrees, vec3& eye, vec3& up) 
{
    // YOUR CODE FOR HW2 HERE
    // Likely the same as in HW 1.  
	
	mat3 rotateMatrix = rotate(degrees, up);
	eye = rotateMatrix*eye;
	
}

void Transform::up(float degrees, vec3& eye, vec3& up) 
{
    // YOUR CODE FOR HW2 HERE 
    // Likely the same as in HW 1.  
	
	vec3 temp_axis = glm::cross(up, eye);
	mat3 rotateMatrix = rotate(-1 * degrees, temp_axis);
	eye = rotateMatrix*eye;
	up = rotateMatrix*up;
	
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
	vec3 n = glm::normalize(eye - center);
	vec3 u = glm::normalize(glm::cross(up, n));
	vec3 v = glm::normalize(glm::cross(n, u));
	mat4 transMatrix(
		1, 0, 0, -1 * eye.x,
		0, 1, 0, -1 * eye.y,
		0, 0, 1, -1 * eye.z,
		0, 0, 0, 1);
	mat4 rotMatrix(
		u.x, u.y, u.z, 0,
		v.x, v.y, v.z, 0,
		n.x, n.y, n.z, 0,
		0, 0, 0, 1);
	mat4 result = transMatrix  * rotMatrix;
	result = glm::transpose(result);
	return result;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
	mat4 perspective_mat = glm::perspective(fovy, aspect, zNear, zFar);	
	float theta = fovy / 2;
	float d = 1/glm::tan(theta);
	float a = (zFar + zNear) / (zNear - zFar);
	float b = 2 * zFar * zNear / (zNear - zFar);
	mat4 prespective_mat(
		d / aspect, 0, 0, 0,
		0, d, 0, 0,
		0, 0, a, b,
		0, 0, -1, 0);
	prespective_mat = glm::transpose(prespective_mat);
    return perspective_mat;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
	mat4 ret(
		sx, 0, 0, 0,
		0, sy, 0, 0,
		0, 0, sz, 0,
		0, 0, 0, 1);
	ret = glm::transpose(ret);
    return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{	
	mat4 ret(
		0, 0, 0, tx,
		0, 0, 0, ty,
		0, 0, 0, tz,
		0, 0, 0, 0);
//	ret = glm::transpose(ret);
    return ret;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
    vec3 x = glm::cross(up,zvec); 
    vec3 y = glm::cross(zvec,x); 
    vec3 ret = glm::normalize(y); 
    return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
