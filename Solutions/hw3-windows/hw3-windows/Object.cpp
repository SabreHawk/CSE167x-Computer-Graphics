#include "Object.h"
#include <iostream>
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
glm::mat4 Object::getTransMat() {
	return this->transform;
}
void Object::disInfo() {
	std::cout << "Type : " << this->type << std::endl;
	std::cout << "Ambient : ";
	for (int i = 0; i < 2; ++i) {
		std::cout << this->ambient[i] << " ";
	}std::cout << std::endl;
	std::cout << "Diffuse : ";
	for (int i = 0; i < 2; ++i) {
		std::cout << this->diffuse[i] << " ";
	}std::cout << std::endl;
	std::cout << "Specular : ";
	for (int i = 0; i < 2; ++i) {
		std::cout << this->specular[i] << " ";
	}std::cout << std::endl;
	std::cout << "Emission : ";
	for (int i = 0; i < 2; ++i) {
		std::cout << this->emission[i] << " ";
	}std::cout << std::endl;
	std::cout << "Shininess : " << this->shininess << std::endl;
}

void Object::transObject() {
}

Sphere::Sphere() {

}

Sphere::Sphere(glm::vec3 _pos, float _r) {
	this->setType("Sphere");
	center_pos = _pos;
	radius = _r;
}

void Sphere::disInfo() {
	Object::disInfo();
	std::cout << "Center Position : ";
	for (int i = 0; i < 2; ++i) {
		std::cout << center_pos[i] << " ";
	}std::cout << std::endl;
	std::cout << "Radius : " << this->radius << std::endl;
}
Triangle::Triangle() {
	this->setType("Triangle");
	this->setTransMat(glm::mat4(1));
}
Triangle::Triangle(glm::vec3 _v[3]) {
	this->setType("Triangle");
	for (int i = 0; i < 3; ++i) {
		vertexs[i] = _v[i];
	}
}

void Triangle::disInfo() {
	Object::disInfo();
	std::cout << "Vertexs Position : " << std::endl;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			std::cout << vertexs[i][j] << " ";;
		}std::cout << std::endl;
	}
}

void Triangle::transObject() {
	glm::vec4 tmp_vec[3];
	for (int i = 0; i < 3; ++i) {
		tmp_vec[i] = glm::vec4(vertexs[i], 1); 
	}
	for (int i = 0; i < 3; ++i) {
		tmp_vec[i] = this->getTransMat()*tmp_vec[i];
	}
	for (int i = 0; i < 3; ++i) {
		vertexs[i] = glm::vec3(tmp_vec[i]);
	}
}

void Triangle::setTransMat(glm::mat4 _m) {
	Object::setTransMat(_m);
	this->transObject();
}
