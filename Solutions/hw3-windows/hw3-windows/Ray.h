#pragma once
#ifndef _SH_RAY_
#define _SH_RAY_
#include <glm/glm.hpp>
class Ray {
private:
	glm::vec3 origin_pos;
	glm::vec3 direction;
public:
	Ray();
	Ray(glm::vec3, glm::vec3);
	glm::vec3 getOriginPos();
	glm::vec3 getDirection();
};
#endif