#pragma once
#ifndef _SH_LIGHT_
#define _SH_LIGHT_
#include <glm\glm.hpp>
class Light {
private:
	int type;
	glm::vec3 light_pos;
	glm::vec3 light_color;
	//glm::vec3 attenuation;
public:
	Light();
	Light(int, glm::vec3, glm::vec3);
	Light(int, glm::vec3, glm::vec3, glm::vec3);
	//void setAttenuation(glm::vec3);
	void disInfo();
	int getType();
	glm::vec3 getPos();
	glm::vec3 getColor();
	//glm::vec3 getAttenuation();
	float computeDecy(float,glm::vec3);
};
#endif // ! 

