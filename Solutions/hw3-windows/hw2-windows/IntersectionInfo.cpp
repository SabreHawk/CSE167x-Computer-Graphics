#include "IntersectionInfo.h"



IntersectionInfo::IntersectionInfo() {
}

IntersectionInfo::IntersectionInfo(bool _i):isIns(_i) {
}

IntersectionInfo::IntersectionInfo(bool _i, float _d, glm::vec3 _p, glm::vec3 _n)
	: isIns(_i), dis(_d), pos(_p), normal(_n) {
}


IntersectionInfo::~IntersectionInfo() {
}

bool IntersectionInfo::getIsIns() {
	return this->isIns;
}

float IntersectionInfo::getDis() {
	return this->dis;
}

glm::vec3 IntersectionInfo::getPos() {
	return this->pos;
}

glm::vec3 IntersectionInfo::getNormal() {
	return this->normal;
}
