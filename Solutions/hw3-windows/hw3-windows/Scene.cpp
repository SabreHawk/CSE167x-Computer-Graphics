//Implement Scene.h

#include <sstream>
#include "Scene.h"
#include "Light.h"
#include "Camera.h"
#include "Transform.h"
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
	glm::vec3 tmp_lookat;
	glm::vec3 tmp_lookfrom;
	glm::vec3 tmp_upvec;
	float tmp_fovy;

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
				for (int i = 0; i < 3; ++i) {
					s_stream >> tmp_diffuse[i];
				}
			} else if (cmd == "specular") {
				for (int i = 0; i < 3; ++i) {
					s_stream >> tmp_specular[i];
				}
			} else if (cmd == "emission") {
				for (int i = 0; i < 3; ++i) {
					s_stream >> tmp_emission[i];
				}
			} else if (cmd == "shininess") {
				for (int i = 0; i < 3; ++i) {
					s_stream >> tmp_shininess[i];
				}
			} else if (cmd == "size") {
				s_stream >> this->image_width;
				s_stream >> this->image_height;
			} else if (cmd == "camera") {
				for (int i = 0; i < 3; ++i) {
					s_stream >> tmp_lookfrom[i];
				}
				for (int i = 0; i < 3; ++i) {
					s_stream >> tmp_lookat[i];
				}
				for (int i = 0; i < 3; ++i) {
					s_stream >> tmp_upvec[i];
				}
				s_stream >> tmp_fovy;
				tmp_upvec = Transform::upvector(tmp_upvec, tmp_lookfrom - tmp_lookat);
				Camera tmp_camera(tmp_lookfrom, tmp_lookat, tmp_upvec, tmp_fovy);
				this->camera = tmp_camera;
			} else if (cmd == "sphere" || cmd == "cube" || cmd == "teapot") {
				Sphere tmp_sphere();
				this->object_vector.push_back(tmp_sphere);
			}
		}
	}
}

void Scene::add_light(Light _light) {
	this->light_vector.push_back(_light);
}