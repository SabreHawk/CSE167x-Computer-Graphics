#include "Object.h"
#include <iostream>
#include <algorithm>
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

std::string Object::getType() {
	return this->type;
}

glm::vec3 Object::getAmbient() {
	return this->ambient;
}

glm::vec3 Object::getDiffuse() {
	return this->diffuse;
}

glm::vec3 Object::getSpecular() {
	return this->specular;
}

glm::vec3 Object::getEmission() {
	return this->emission;
}

float Object::getShininess() {
	return this->shininess;
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
float Sphere::intersectRay(Ray _r) {
	glm::vec3 tmp_vec = _r.getOriginPos() - this->center_pos;
	glm::vec2 paras;
	float out_dis;
	float delta = (pow(glm::length(_r.getDirection()), 2) - 1)*pow(glm::length(tmp_vec), 2) + pow(glm::length(this->center_pos), 2);
	if (delta < 0) {
		return -1;
	} else {
		paras[0] = -1 * glm::dot(tmp_vec, _r.getDirection()) + sqrt(delta);
		paras[1] = -1 * glm::dot(tmp_vec, _r.getDirection()) - sqrt(delta);
		if (paras[0] == -1 && paras[1] == -1) {//No Intersection
			return -1;
		} else if (paras[0] == paras[1] && paras[0] >= 0) {
			out_dis = paras[0];
		} else if (paras[0] * paras[1] <= 0) {
			out_dis = paras[0] > 0 ? paras[0] : paras[1];
		} else if (paras[0] > 0 && paras[1] > 0) {
			out_dis = paras[0] < paras[1] ? paras[0] : paras[1];
		}
	}
	return out_dis;
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
	this->setTransMat(glm::mat4(1)); 
	this->normal = glm::normalize(glm::cross(vertexs[1] - vertexs[0], vertexs[2] - vertexs[0]));
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

float Triangle::intersectRay(Ray _r) {
	if (glm::dot(_r.getDirection(), this->normal) == 0) {
		return -1;
	}
	float tmp_t = (glm::dot(this->vertexs[0], this->normal) - glm::dot(_r.getOriginPos(), this->normal)) / glm::dot(_r.getDirection(), this->normal);
	glm::vec3 tmp_pos = _r.getOriginPos() + tmp_t * _r.getDirection();
	glm::vec3 edge10 = this->vertexs[1] - this->vertexs[0];
	glm::vec3 edge21 = this->vertexs[2] - this->vertexs[1];
	glm::vec3 edge02 = this->vertexs[0] - this->vertexs[2];
	if (glm::dot(glm::cross(edge10, tmp_pos - this->vertexs[0]), this->normal) >= 0 &&
		glm::dot(glm::cross(edge21, tmp_pos - this->vertexs[1]), this->normal) >= 0 &&
		glm::dot(glm::cross(edge02, tmp_pos - this->vertexs[2]), this->normal) >= 0) {
		return tmp_t;
	} else {
		return -1;
	}
}

glm::vec3 Triangle::getNormal() {
	return this->normal;
}

glm::vec3 Triangle::computeLambertLight(glm::vec3 _pos,Light _l) {
	float light_dis = glm::length(_pos - _l.getPos());
	glm::vec3 light_dir = _l.getPos() - _pos;
	glm::vec3 i = _l.getColor() / _l.computeDecy(light_dis);
	float nDotL = glm::dot(this->normal, light_dir);
	if (nDotL < 0) {
		nDotL = 0;
	}
	return i * this->getDiffuse() *_l.getColor() * nDotL;
}

glm::vec3 Triangle::computePhongLight(glm::vec3 _pos,Light _l,Ray _r) {
	float light_dis = glm::length(_pos - _l.getPos()); 
	glm::vec3 light_dir = _l.getPos() - _pos;
	glm::vec3 eye_dir = _r.getOriginPos() - _pos;
	glm::vec3 half_vec = glm::normalize(light_dir + eye_dir);
	glm::vec3 i = _l.getColor() / _l.computeDecy(light_dis);
	float nDotL = glm::dot(this->normal, half_vec);
	if (nDotL < 0) {
		nDotL = 0;
	}
	return i * this->getSpecular()*_l.getColor()*pow(nDotL, getShininess());
}

 