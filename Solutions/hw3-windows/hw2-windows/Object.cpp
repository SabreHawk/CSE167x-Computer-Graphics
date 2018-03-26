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

IntersectionInfo Sphere::intersectRay(Ray & _r) {
	glm::vec4 tmp_pp=  glm::inverse(this->getTransMat())*glm::vec4(_r.getOriginPos(), 1);
	glm::vec3 trans_p = glm::vec3(tmp_pp.x / tmp_pp.w, tmp_pp.y / tmp_pp.w, tmp_pp.z / tmp_pp.w);
	glm::vec3 trans_dir = glm::normalize(glm::vec3(glm::inverse(this->getTransMat()) * glm::vec4(_r.getDirection(), 0)));
	
	Ray tmp_r(trans_p, trans_dir);
	glm::vec3 tmp_vec = tmp_r.getOriginPos() - this->center_pos;		
	float a = glm::dot(tmp_r.getDirection(), tmp_r.getDirection());
	float b = 2 * glm::dot(tmp_r.getDirection(), tmp_vec);
	float c = glm::dot(tmp_vec, tmp_vec) - pow(this->radius, 2);
	float delta = b * b - 4 * a * c;
	if (delta <= 0) {
		return IntersectionInfo(false);
		//return INFINITY;
	} 
	float root_0 = (-1 * sqrt(delta) - b) / (2 * a);
	float root_1 = (sqrt(delta) - b) / (2 * a);
	float tmp_out = 0;
	if (root_0 * root_1 <= 0) {
		return IntersectionInfo(false);
	} else {
		tmp_out = std::min(root_0, root_1);
	}
	if (tmp_out < 0.00001f) {
		return IntersectionInfo(false);
	}
	glm::vec4 world_ins_pos = this->getTransMat() * glm::vec4(trans_p + tmp_out * trans_dir, 1);
	glm::vec3 tmp_ins_p = glm::vec3(world_ins_pos.x / world_ins_pos.w, world_ins_pos.y / world_ins_pos.w, world_ins_pos.z / world_ins_pos.w);
	glm::vec3 tmp_normal = glm::normalize(trans_p + tmp_out * trans_dir - this->center_pos);
	tmp_normal = glm::normalize(glm::vec3(glm::inverse(glm::transpose(this->getTransMat())) * glm::vec4(tmp_normal, 0)));
	tmp_out = glm::length(tmp_ins_p - _r.getOriginPos());
	return IntersectionInfo(true,tmp_out,tmp_ins_p,tmp_normal);
}

IntersectionInfo Sphere::shadowIntersection(Ray & _r) {
	glm::vec4 tmp_pp = glm::inverse(this->getTransMat())*glm::vec4(_r.getOriginPos(), 1);
	glm::vec3 trans_p = glm::vec3(tmp_pp.x / tmp_pp.w, tmp_pp.y / tmp_pp.w, tmp_pp.z / tmp_pp.w);
	glm::vec3 trans_dir = glm::normalize(glm::vec3(glm::inverse(this->getTransMat()) * glm::vec4(_r.getDirection(), 0)));

	Ray tmp_r(trans_p, trans_dir);
	glm::vec3 tmp_vec = tmp_r.getOriginPos() - this->center_pos;
	float a = glm::dot(tmp_r.getDirection(), tmp_r.getDirection());
	float b = 2 * glm::dot(tmp_r.getDirection(), tmp_vec);
	float c = glm::dot(tmp_vec, tmp_vec) - pow(this->radius, 2);
	float delta = b * b - 4 * a * c;
	if (delta <= 0) {
		return IntersectionInfo(false);
		//return INFINITY;
	}
	float root_0 = (-1 * sqrt(delta) - b) / (2 * a);
	float root_1 = (sqrt(delta) - b) / (2 * a);
	float tmp_out = 0;
	if (root_0 * root_1 <= 0) {
		return IntersectionInfo(false);
	} else {
		tmp_out = std::min(root_0, root_1);
	}
	if (tmp_out < 0.00001f) {
		return IntersectionInfo(false);
	}
	glm::vec4 world_ins_pos = this->getTransMat() * glm::vec4(trans_p + tmp_out * trans_dir, 1);
	glm::vec3 tmp_ins_p = glm::vec3(world_ins_pos.x / world_ins_pos.w, world_ins_pos.y / world_ins_pos.w, world_ins_pos.z / world_ins_pos.w);
	glm::vec3 tmp_normal = glm::normalize(trans_p + tmp_out * trans_dir - this->center_pos);
	tmp_normal = glm::normalize(glm::vec3(glm::inverse(glm::transpose(this->getTransMat())) * glm::vec4(tmp_normal, 0)));
	tmp_out = glm::length(tmp_ins_p - _r.getOriginPos());
	return IntersectionInfo(true, tmp_out, tmp_ins_p, tmp_normal);
}
void Sphere::transObject() {
}

glm::vec3 Sphere::getNormal(glm::vec3 _pos) {
	glm::vec4 tmp_pp = glm::inverse(this->getTransMat()) * glm::vec4(_pos, 1);
	glm::vec3 tmp_ppp = glm::vec3(tmp_pp.x / tmp_pp.w, tmp_pp.y / tmp_pp.w, tmp_pp.z / tmp_pp.w);
	return glm::normalize(glm::vec3(glm::transpose(glm::inverse(this->getTransMat()))*glm::vec4((tmp_ppp - this->center_pos), 0)));
}

glm::vec3 Sphere::getReflectionRay(Ray &_r) {
	IntersectionInfo tmp_ins_info = intersectRay(_r);
	return glm::normalize(2 * glm::dot(float(-1)*_r.getDirection(), tmp_ins_info.getNormal())*tmp_ins_info.getNormal() + _r.getDirection());
}

glm::vec3 Sphere::computeLambertLight(glm::vec3 & _l_dir,glm::vec3 & _s_normal, Light & _l) {
	float nDotL = glm::dot(_s_normal, _l_dir);
	if (nDotL < 0) {
		nDotL = 0;
	}
	return  this->getDiffuse()*_l.getColor() * nDotL;
}

glm::vec3 Sphere::computePhongLight(glm::vec3 & _l_dir,glm::vec3 &_e_dir,glm::vec3 &_s_normal, Light & _l) {
	glm::vec3 half_vec = glm::normalize(_e_dir + _l_dir);
	float nDotL = glm::dot(_s_normal, half_vec);
	if (nDotL < 0) {
		nDotL = 0;
	}
	return this->getSpecular()*_l.getColor()*pow(nDotL, this->getShininess());
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
	this->normal = glm::normalize(glm::cross(vertexs[1]- vertexs[0], vertexs[2] - vertexs[0]));
}

void Triangle::disInfo() {
	Object::disInfo();
	std::cout << "Vertexs Position : " << std::endl;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			std::cout << vertexs[i][j] << " ";;
		}std::cout << std::endl;
	}
	std::cout << "Normal : " << std::endl;
	for (int i = 0; i < 3; ++i) {
		std::cout << this->normal[i] << " ";
	}std::cout << std::endl;
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

IntersectionInfo Triangle::intersectRay(Ray & _r) {
	if (glm::dot(_r.getDirection(), this->normal)>= 0) {
		return IntersectionInfo(false);
	}
	float tmp_t = (glm::dot(this->vertexs[0], this->normal) - glm::dot(_r.getOriginPos(), this->normal)) / glm::dot(_r.getDirection(), this->normal);
	if (tmp_t <= 0) {
		return IntersectionInfo(false);
	}
	glm::vec3 tmp_pos = _r.getOriginPos() + tmp_t * _r.getDirection();
	glm::vec3 edge10 = this->vertexs[1] - this->vertexs[0];
	glm::vec3 edge21 = this->vertexs[2] - this->vertexs[1];
	glm::vec3 edge02 = this->vertexs[0] - this->vertexs[2];
	if (glm::dot(glm::cross(edge10, tmp_pos - this->vertexs[0]), this->normal) >= 0 &&
		glm::dot(glm::cross(edge21, tmp_pos - this->vertexs[1]), this->normal) >= 0 &&
		glm::dot(glm::cross(edge02, tmp_pos - this->vertexs[2]), this->normal) >= 0) {
		return IntersectionInfo(true, tmp_t, tmp_pos, this->normal);
	} else {
		return IntersectionInfo(false);
	}
}

IntersectionInfo Triangle::shadowIntersection(Ray & _r) {
	if (glm::dot(_r.getDirection(), this->normal) == 0) {
		return IntersectionInfo(false);
	}
	float tmp_t = (glm::dot(this->vertexs[0], this->normal) - glm::dot(_r.getOriginPos(), this->normal)) / glm::dot(_r.getDirection(), this->normal);
	if (tmp_t <= 0) {
		return IntersectionInfo(false);
	}
	glm::vec3 tmp_pos = _r.getOriginPos() + tmp_t * _r.getDirection();
	glm::vec3 edge10 = this->vertexs[1] - this->vertexs[0];
	glm::vec3 edge21 = this->vertexs[2] - this->vertexs[1];
	glm::vec3 edge02 = this->vertexs[0] - this->vertexs[2];
	if (glm::dot(glm::cross(edge10, tmp_pos - this->vertexs[0]), this->normal) >= 0 &&
		glm::dot(glm::cross(edge21, tmp_pos - this->vertexs[1]), this->normal) >= 0 &&
		glm::dot(glm::cross(edge02, tmp_pos - this->vertexs[2]), this->normal) >= 0) {
		return IntersectionInfo(true, tmp_t, tmp_pos, this->normal);
	} else {
		return IntersectionInfo(false);
	}
}
glm::vec3 Triangle::getNormal(glm::vec3 _p) {
	return this->normal;
}

glm::vec3 Triangle::computeLambertLight(glm::vec3 & _l_dir,glm::vec3 &_t_normal,Light & _l) {
	float nDotL = glm::dot(_t_normal, _l_dir);
	if (nDotL < 0) {
		nDotL = 0;
	}
	return this->getDiffuse() *_l.getColor() * nDotL;
}

glm::vec3 Triangle::computePhongLight(glm::vec3 & _l_dir, glm::vec3 & _e_dir, glm::vec3 & _t_norma, Light & _l) {
	glm::vec3 half_vec = glm::normalize(_l_dir + _e_dir);
	float nDotL = glm::dot(_t_norma, half_vec);
	if (nDotL < 0) {
		nDotL = 0;
	}
	return  this->getSpecular()*_l.getColor()*pow(nDotL, getShininess());
}

glm::vec3 Triangle::getReflectionRay(Ray & _r) {
	IntersectionInfo tmp_ins_info = intersectRay(_r);
	return glm::normalize(2 * glm::dot(float(-1)*_r.getDirection(), tmp_ins_info.getNormal())*tmp_ins_info.getNormal() + _r.getDirection());
}

 