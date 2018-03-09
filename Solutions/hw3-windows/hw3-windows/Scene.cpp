//Implement Scene.h

#include <sstream>
#include "Scene.h"
#include "Light.h"

Scene::Scene() {
}

void Scene::scene_analyzer(std::vector<std::string> _content) {
	std::vector<std::string>::iterator itor;
	std::string tmp_str;
	std::string cmd;
	std::vector<int> data_vector;
	glm::vec3 tmp_ambient;
	glm::vec3 tmp_diffuse;
	glm::vec3 tmp_specular;
	glm::vec3 tmp_emission;
	glm::vec3 tmp_shininess;

	for (itor = _content.begin(); itor != _content.end(); ++itor) {
		tmp_str = *itor;

		if ((tmp_str.find_first_not_of(" \t\r\n") != std::string::npos) && (tmp_str[0] != '#')) {
			std::stringstream s_stream(tmp_str);
			s_stream >> cmd;
			if (cmd == "point") {
				glm::vec3 tmp_pos;
				glm::vec3 tmp_color;
				for (int i = 0; i < 2; ++i) {
					s_stream >> tmp_pos[i];
				}
				for (int i = 3; i < 5; ++i) {
					s_stream >> tmp_color[i];
				}
				Light tmp_light(1,tmp_pos, tmp_color);
			} else if (cmd == "directional") {
				glm::vec3 tmp_pos;
				glm::vec3 tmp_color;
				for (int i = 0; i < 2; ++i) {
					s_stream >> tmp_pos[i];
				}
				for (int i = 3; i < 5; ++i) {
					s_stream >> tmp_color[i];
				}
				Light tmp_light(0, tmp_pos, tmp_color);
				this->add_light(tmp_light);
			} else if (cmd == "ambient") {
				for (int i = 0; i < 3; ++i) {
					s_stream >> tmp_ambient[i];
				}
			} else if (cmd == "diffuse") {


			}
		}
	}
}

void Scene::add_light(Light _light) {
	this->light_vector.push_back(_light);
}