#pragma once
#include "Light.h"
#include <iostream>

Light::Light() {
	attenuation = glm::vec3(1, 0, 0);
}

Light::Light(int _type, glm::vec3 _pos, glm::vec3 _color) {
	type = _type;
	light_pos = _pos;
	light_color = _color;
	attenuation = glm::vec3(1, 0, 0);
}

Light::Light(int _type,glm::vec3 _pos, glm::vec3 _color,glm::vec3 _att) {
	type = _type;
	light_pos = _pos;
	light_color = _color;
	attenuation = _att;
}

void Light::setAttenuation(glm::vec3 _att) {
	attenuation = _att;
}

void Light::disInfo() {
	std::cout << "Type : " << this->type << std::endl;
	std::cout << "Position : ";
	for (int i = 0; i < 2; ++i) {
		std::cout << this->light_pos[i] << " ";
	}std::cout << std::endl;
	std::cout << "Color : ";
	for (int i = 0; i < 2; ++i) {
		std::cout << this->light_color[i] << " ";
	}std::cout << std::endl;
	std::cout << "Attenuation : ";
	for (int i = 0; i < 2; ++i) {
		std::cout << this->attenuation[i] << " ";
	}std::cout << std::endl;

}

int Light::getType() {
	return this->type;
}

glm::vec3 Light::getPos() {
	return this->light_pos;
}

glm::vec3 Light::getColor() {
	return this->light_color;
}

float Light::computeDecy(float _d,glm::vec3 _a) {
	float out_d = 0;
	for (int i = 0; i < 3; ++i) {
		out_d += _a[i] * pow(_d, i);
	}
	return out_d;
}
