#include "Object.h"

void Object::setType(std::string _type) {
	this->type = _type;
}

void Object::setAmbient(glm::vec4 _a) {
	this->ambient = _a;
}

void Object::setDiffuse(glm::vec4 _d) {
	this->diffuse = _d;
}

void Object::setSpecular(glm::vec4 _s) {
	this->setSpecular = _s;
}

void Object::setEmission(glm::vec4 _e) {
	this->emission = _e;
}
