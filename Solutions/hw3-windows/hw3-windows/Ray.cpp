#include "Ray.h"

Ray::Ray() {

}

Ray::Ray(glm::vec3 _pos, glm::vec3 _dir) :origin_pos(_pos),direction(glm::normalize(_dir)){

}

glm::vec3 Ray::getOriginPos() {
	return this->origin_pos;
}

glm::vec3 Ray::getDirection() {
	return this->direction;
}
