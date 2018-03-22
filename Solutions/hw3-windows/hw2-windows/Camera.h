#pragma once
#ifndef _SH_CAMERA_
#define _SH_CAMERA_
#include <glm/glm.hpp>

class Camera {
private:
	glm::vec3 camera_position;
	glm::vec3 target_position;
	glm::vec3 up_vector;
	float fov_y;
	glm::vec3 u;
	glm::vec3 v;
	glm::vec3 w;
public:
	Camera();
	Camera(glm::vec3, glm::vec3, glm::vec3,float);
	glm::vec3 getCameraPos();
	glm::vec3 getTargetPos();
	glm::vec3 getUpVector();
	glm::vec3 getDirection();
	float getFovY();
	float getFovX(int,int);
	glm::vec3 getU();
	glm::vec3 getV();
	glm::vec3 getW();
};
#endif
