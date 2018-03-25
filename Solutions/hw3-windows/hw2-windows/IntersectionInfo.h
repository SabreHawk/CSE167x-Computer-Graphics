#pragma once
#ifndef __SH_INTERSECTIONINFO_
#include <glm\glm.hpp>
class IntersectionInfo {
private:
	bool isIns;
	//bool isShadow;
	float dis;
	glm::vec3 pos;
	glm::vec3 normal;
public:
	IntersectionInfo();
	IntersectionInfo(bool);
	IntersectionInfo(bool, float, glm::vec3, glm::vec3);
	~IntersectionInfo();

	bool getIsIns();
//	bool getIsShadow();
	float getDis();
	glm::vec3 getPos();
	glm::vec3 getNormal();
};
#define __SH_INTERSECTIONINFO_
#endif // !__SH_INTERSECTIONINFO_



