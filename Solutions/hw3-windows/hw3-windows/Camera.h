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
};
#endif
