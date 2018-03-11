#include "Object.h"

Object::Object() {
}

void Object::setType(std::string _type) {
	this->type = _type;
}

void Object::setAmbient(glm::vec3 _a) {
	this->ambient = _a;
}

void Object::setDiffuse(glm::vec3 _d) {
	this->diffuse = _d;
}

void Object::setSpecular(glm::vec3 _s) {
	this->specular = _s;
}

void Object::setEmission(glm::vec3 _e) {
	this->emission = _e;
}

void Object::setShininess(float _s) {
	this->shininess = _s;
}

void Object::setTransMat(glm::mat4 _m) {
	this->transform = _m;
}

Triangle::Triangle(glm::vec3 _v[3]) {
	for (int i = 0; i < 3; ++i) {
		vertexs[i] = _v[i];
	}
}

Sphere::Sphere() {
}

Sphere::Sphere(glm::vec3 _pos, float _r) {
	center_pos = _pos;
	radius = _r;
}