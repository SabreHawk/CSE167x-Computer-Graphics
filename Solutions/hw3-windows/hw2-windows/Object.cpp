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
	for (int i = 0; i < 3; ++i) {
		std::cout << this->ambient[i] << " ";
	}std::cout << std::endl;
	std::cout << "Diffuse : ";
	for (int i = 0; i < 3; ++i) {
		std::cout << this->diffuse[i] << " ";
	}std::cout << std::endl;
	std::cout << "Specular : ";
	for (int i = 0; i < 3; ++i) {
		std::cout << this->specular[i] << " ";
	}std::cout << std::endl;
	std::cout << "Emission : ";
	for (int i = 0; i < 3; ++i) {
		std::cout << this->emission[i] << " ";
	}std::cout << std::endl;
	std::cout << "Shininess : " << this->shininess << std::endl;
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
	this->setTransMat(glm::mat4(1));
}

Sphere::Sphere(glm::vec3 _pos, float _r) {
	this->setType("Sphere");
	center_pos = _pos;
	radius = _r;
	this->setTransMat(glm::mat4(1));
}

void Sphere::disInfo() {
	Object::disInfo();
	std::cout << "Center Position : ";
	for (int i = 0; i < 3; ++i) {
		std::cout << center_pos[i] << " ";
	}std::cout << std::endl;
	std::cout << "Radius : " << this->radius << std::endl;
}

float Sphere::intersectRay(Ray & _r) {

	glm::vec3 trans_p = glm::vec3(glm::inverse(this->getTransMat())*glm::vec4(_r.getOriginPos(), 1));
	glm::vec3 trans_dir = glm::normalize(glm::vec3(glm::inverse(this->getTransMat()) * glm::vec4(_r.getDirection(), 0)));
	Ray tmp_r(trans_p, trans_dir);
	//std::cout << "Trans Vec " << std::endl;
	//for (int i = 0; i < 3; ++i) {
	//	std::cout << _r.getOriginPos()[i] << " ";
	//}std::cout << std::endl;
	glm::vec3 tmp_vec = tmp_r.getOriginPos() - this->center_pos;
	float a = glm::dot(tmp_r.getDirection(), tmp_r.getDirection());
	float b = 2 * glm::dot(tmp_r.getDirection(), tmp_vec);
	float c = glm::dot(tmp_vec, tmp_vec) - pow(this->radius, 2);
	float delta = b * b - 4 * a * c;
	if (delta < 0) {
		return INFINITY;
	} 
	float root_0 = (-1 * sqrt(delta) - b) / (2 * a);
	float root_1 = (sqrt(delta) - b) / (2 * a);
	float tmp_out = 0;
	if (root_0 * root_1 <= 0) {
		return INFINITY;
	} else {
		tmp_out = std::min(root_0, root_1);
	}
	//std::cout << "PRE : " << tmp_out << std::endl;
	glm::vec3 tmp_ins_p = glm::vec3(this->getTransMat() * glm::vec4(trans_p + tmp_out * trans_dir, 1));
	//std::cout << "Trans Pos " << std::endl;
	//for (int i = 0; i < 3; ++i) {
	//	std::cout << trans_p[i] << " ";
	//}std::cout << std::endl;
	//std::cout << "Trans dir " << std::endl;
	//for (int i = 0; i < 3; ++i) {
	//	std::cout << trans_p[i] << " ";
	//}std::cout << std::endl;
	//std::cout << "PRE : " << tmp_out << std::endl;
	//std::cout << "tmp_ins_p " << std::endl;
	//for (int i = 0; i < 3; ++i) {
	//	std::cout << tmp_ins_p[i] << " ";
	//}std::cout << std::endl;
	tmp_out = glm::length(tmp_ins_p - _r.getOriginPos());

	
	return tmp_out;
}

void Sphere::transObject() {
}

glm::vec3 Sphere::getReflectionRay(Ray &_r) {
	float tmp_t = intersectRay(_r);
	if (tmp_t == INFINITY) {
		return glm::vec3(0, 0, 0);
	}

	glm::vec3 tmp_pos = glm::vec3(this->getTransMat() * glm::vec4(_r.getOriginPos() + tmp_t * _r.getDirection(), 0));
	glm::vec3 tmp_normal = glm::vec3(glm::normalize(glm::transpose(glm::inverse(this->getTransMat()))*glm::vec4((tmp_pos - this->center_pos), 0)));
	return glm::normalize(2 * glm::dot(_r.getDirection(), tmp_normal)*tmp_normal - _r.getDirection());
}

glm::vec3 Sphere::computeLambertLight(glm::vec3 & _pos, Light & _l) {
	float light_dis = glm::length(_pos - _l.getPos());
	glm::vec3 light_dir = _l.getPos() - _pos;
	float i = 1;
	//if (_l.getType() == 1) {
	//	i = 1 / _l.computeDecy(light_dis);
	//}
	glm::vec3 s_normal = glm::vec3(glm::normalize(glm::transpose(glm::inverse(this->getTransMat()))*glm::vec4((_pos - this->center_pos), 0)));
	float nDotL = glm::dot(s_normal, light_dir);
	if (nDotL < 0) {
		nDotL = 0;
	}
	return i * this->getDiffuse()*_l.getColor() * nDotL;
}

glm::vec3 Sphere::computePhongLight(glm::vec3 & _pos, Light & _l,Ray & _r) {
	float light_dis = glm::length(_pos - _l.getPos());
	glm::vec3 light_dir = glm::normalize(_l.getPos() - _pos);
	float i = 1;
	//if (_l.getType() == 1) {
	//	i = 1 / _l.computeDecy(light_dis);
	//}
	glm::vec3 s_normal = glm::vec3(glm::normalize(glm::transpose(glm::inverse(this->getTransMat()))*glm::vec4((_pos - this->center_pos), 0)));
	glm::vec3 eye_dir = _r.getOriginPos() - _pos;
	glm::vec3 half_vec = glm::normalize(eye_dir + light_dir);
	float nDotL = glm::dot(s_normal, half_vec);
	if (nDotL < 0) {
		nDotL = 0;
	}
	return i * this->getSpecular()*_l.getColor()*pow(nDotL, getShininess());
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
	//this->setTransMat(glm::mat4(1)); 
	this->normal = glm::normalize(glm::cross(vertexs[2]- vertexs[0], vertexs[1] - vertexs[0]));
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
	//this->transObject();
}

float Triangle::intersectRay(Ray & _r) {
	if (glm::dot(_r.getDirection(), this->normal) == 0) {
		return INFINITY;
	}
	float tmp_t = (glm::dot(this->vertexs[0], this->normal) - glm::dot(_r.getOriginPos(), this->normal)) / glm::dot(_r.getDirection(), this->normal);
	if (tmp_t < 0) {
		return INFINITY;
	}
	glm::vec3 tmp_pos = _r.getOriginPos() + tmp_t * _r.getDirection();
	glm::vec3 edge20 = this->vertexs[2] - this->vertexs[0];
	glm::vec3 edge12 = this->vertexs[1] - this->vertexs[2];
	glm::vec3 edge01 = this->vertexs[0] - this->vertexs[1];
	if (glm::dot(glm::cross(edge20, tmp_pos - this->vertexs[0]), this->normal) >= 0 &&
		glm::dot(glm::cross(edge12, tmp_pos - this->vertexs[2]), this->normal) >= 0 &&
		glm::dot(glm::cross(edge01, tmp_pos - this->vertexs[1]), this->normal) >= 0) {
		return tmp_t;
	} else {
		return INFINITY;
	}
}

glm::vec3 Triangle::getNormal() {
	return this->normal;
}

glm::vec3 Triangle::computeLambertLight(glm::vec3 & _pos,Light & _l) {
	float light_dis = glm::length(_pos - _l.getPos());
	glm::vec3 light_dir = _l.getPos() - _pos;
	glm::vec3 i = _l.getColor() / _l.computeDecy(light_dis);
	float nDotL = glm::dot(this->normal, light_dir);
	if (nDotL < 0) {
		nDotL = 0;
	}
	return i * this->getDiffuse() *_l.getColor() * nDotL;
}

glm::vec3 Triangle::computePhongLight(glm::vec3 & _pos,Light & _l,Ray & _r) {
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

glm::vec3 Triangle::getReflectionRay(Ray & _r) {
	return glm::normalize(2 * glm::dot(float(-1)*_r.getDirection(), this->normal)*this->normal + _r.getDirection());
}

 