#pragma once
#ifndef _SH_LIGHT_
#define _SH_LIGHT_
#include <glm\glm.hpp>
class Light {
private:
	int type;
	glm::vec3 light_pos;
	glm::vec3 light_color;
};
#endif // ! 

