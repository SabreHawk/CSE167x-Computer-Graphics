#pragma once
#include "Light.h"

Light::Light() {

}

Light::Light(int _type,glm::vec3 _pos, glm::vec3 _color) {
	type = _type;
	light_pos = _pos;
	light_color = _color;
}
