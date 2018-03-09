#pragma once
#ifndef _SH_LIGHT_
#define _SH_LIGHT_
#include <glm\glm.hpp>
class Light {
private:
	int type;
	glm::vec3 light_pos;
	glm::vec3 light_color;
public:
	Light() {
	}
	Light(int,glm::vec3, glm::vec3);
};
#endif // ! 

