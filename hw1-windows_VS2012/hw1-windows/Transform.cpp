// Transform.cpp: implementation of the Transform class.


#include "Transform.h"
#include <stdio.h>
#include <iostream>
using namespace std;

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
  // YOUR CODE FOR HW1 HERE
	double  radian = degrees * pi / 180;
	vec3 temp_axis = glm::normalize(axis);
	double cosA = cos(radian);
	double oneC = 1 - cosA;
	double sinA = sin(radian);
	mat3 rotate_matrix;
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

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE
	mat3 rotateMatrix = rotate(degrees,up);
	eye = rotateMatrix*eye;
//	up = rotateMatrix*up;
	//cout << "Rotate Matrix : " << endl;
	//for (int i = 0; i < 3; ++i) {
	//	for (int j = 0; j < 3; ++j) {
	//		cout << rotateMatrix[i][j] << " ";
	//	}cout << endl;
	//}cout << endl;
	//cout << "<info>" << endl;
	//cout << "eye : " << eye.x << " " << eye.y << " " << eye.z << endl;
	//cout << "up : " << up.x << " " << up.y << " " << up.z << endl;
	//cout << "<info/>" << endl;

//	printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE 
	vec3 temp_axis = glm::cross(up,eye);
	mat3 rotateMatrix = rotate(-1*degrees, temp_axis);
	eye = rotateMatrix*eye;
	up = rotateMatrix*up;

	//cout << " vertical Rotate Matrix : " << endl;
	//for (int i = 0; i < 3; ++i) {
	//	for (int j = 0; j < 3; ++j) {
	//		cout << rotateMatrix[i][j] << " ";
	//	}cout << endl;
	//}cout << endl;
	//cout << "<info>" << endl;
	//cout <<"axis : " << temp_axis.x << " " << temp_axis.y << " " << temp_axis.z << endl;
	//cout << "eye : "<<eye.x << " " << eye.y << " " << eye.z << endl;
	//cout << "up : "<<up.x << " " << up.y << " " << up.z << endl;
	//cout << "<info/>" << endl;
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  // YOUR CODE FOR HW1 HERE
	vec3 n = glm::normalize(eye);
	vec3 u = glm::normalize(glm::cross(up, n));
	vec3 v = glm::normalize(glm::cross(n, u));
	mat4 transMatrix(1, 0, 0, -1 * eye.x,
					 0, 1, 0, -1 * eye.y,
					 0, 0, 1, -1 * eye.z,
					 0, 0, 0, 1);
	mat4 rotMatrix(u.x, u.y, u.z, 0, 
				   v.x, v.y, v.z, 0,
				   n.x, n.y, n.z, 0,
		           0, 0, 0, 1);
	mat4 result = transMatrix  * rotMatrix;
	result = glm::transpose(result);
 //   You will change this return call
	//for (int i = 0; i < 4; ++i) {
	//	for (int j = 0; j < 4; ++j) {
	//		cout << result[i][j] << " ";
	//	}cout << endl;
	//}
	return result;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
