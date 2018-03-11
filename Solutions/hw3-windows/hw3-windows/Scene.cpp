//Implement Scene.h

#include <sstream>
#include "Scene.h"
#include "Light.h"
#include "Camera.h"
#include "Transform.h"
#include <stack>
#include <iostream>

void Scene::scene_analyzer(std::vector<std::string> _content) {
	std::vector<std::string>::iterator itor;
	std::string tmp_str;
	std::string cmd;
	std::vector<int> data_vector;
	glm::vec3 tmp_ambient(0.2, 0.2, 0.2);
	glm::vec3 tmp_diffuse(0, 0, 0);
	glm::vec3 tmp_specular(0, 0, 0);
	glm::vec3 tmp_emission(0, 0, 0);
	float tmp_shininess = 0;

	glm::vec3 tmp_lookat;
	glm::vec3 tmp_lookfrom;
	glm::vec3 tmp_upvec;
	float tmp_fovy;
	std::vector<glm::vec3> vertex_vec;
	std::stack<glm::mat4> transfstack;
	transfstack.push(glm::mat4(1));
	for (itor = _content.begin(); itor != _content.end(); ++itor) {
		tmp_str = *itor;

		if ((tmp_str.find_first_not_of(" \t\r\n") != std::string::npos) && (tmp_str[0] != '#')) {
			std::stringstream s_stream(tmp_str);
			s_stream >> cmd;
			if (cmd == "point") {
				glm::vec3 tmp_pos;
				glm::vec3 tmp_color;
				for (int i = 0; i < 3; ++i) {
					s_stream >> tmp_pos[i];
				}
				for (int i = 0; i < 3; ++i) {
					s_stream >> tmp_color[i];
				}
				Light tmp_light(1,tmp_pos, tmp_color);
				this->add_light(tmp_light);
			} else if (cmd == "directional") {
				glm::vec3 tmp_pos;
				glm::vec3 tmp_color;
				for (int i = 0; i < 3; ++i) {
					s_stream >> tmp_pos[i];
				}
				for (int i = 0; i < 3; ++i) {
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
				s_stream >> tmp_shininess;
			} else if (cmd == "size") {
				s_stream >> this->image_width;
				s_stream >> this->image_height;
			} else if (cmd == "output") {
				s_stream >> this->scene_name;
			} else if (cmd == "camera")  
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
			} else if (cmd == "sphere") {
				glm::vec3 tmp_pos;
				float tmp_radius;
				for (int i = 0; i < 3; ++i) {
					s_stream >> tmp_pos[i];
				}
				s_stream >> tmp_radius;
				Sphere * tmp_sphere = new Sphere(tmp_pos,tmp_radius);
				tmp_sphere->setAmbient(tmp_ambient);
				tmp_sphere->setDiffuse(tmp_diffuse);
				tmp_sphere->setEmission(tmp_emission);
				tmp_sphere->setSpecular(tmp_specular);
				tmp_sphere->setShininess(tmp_shininess);
				tmp_sphere->setTransMat(transfstack.top());
				this->object_vector.push_back(tmp_sphere);
			} else if (cmd == "vertex") {
				vec3 tmp_vec;
				for (int i = 0; i < 3; ++i) {
					s_stream >> tmp_vec[i];
				}
				vertex_vec.push_back(tmp_vec);
			} else if (cmd == "tri") {
				vec3 tmp_vec;
				for (int i = 0; i < 3; ++i) {
					s_stream >> tmp_vec[i];
				}
				vec3 tmp_vertexs[3];
				for (int i = 0; i < 3; ++i) {
					for (int j = 0; j < 3; ++j) {
						tmp_vertexs[i][j] = vertex_vec[tmp_vec[i]][j];
					}
				}
				Triangle * tmp_tri = new Triangle(tmp_vertexs);
				tmp_tri->setAmbient(tmp_ambient);
				tmp_tri->setDiffuse(tmp_diffuse);
				tmp_tri->setEmission(tmp_emission);
				tmp_tri->setSpecular(tmp_specular);
				tmp_tri->setShininess(tmp_shininess);
				tmp_tri->setTransMat(transfstack.top());
				this->object_vector.push_back(tmp_tri);
			} else if (cmd == "pushTransform") {
				transfstack.push(transfstack.top());
			} else if (cmd == "popTransform") {
				if (transfstack.size() <= 1) {
					std::cerr << "Stack has no elements.  Cannot Pop\n";
				} else {
					transfstack.pop();
				}
			} else if (cmd == "translate") {
				glm::vec3 tmp_vec;
				for (int i = 0; i < 3; ++i) {
					s_stream >> tmp_vec[i];
				}
				mat4 &T = transfstack.top();
				mat4 M = Transform::translate(tmp_vec[0], tmp_vec[1], tmp_vec[2]);
				T = T * M; 
			} else if (cmd == "scale") {
				glm::vec3 tmp_vec;
				for (int i = 0; i < 3; ++i) {
					s_stream >> tmp_vec[i];
				}
				mat4 &T = transfstack.top();
				mat4 M = Transform::scale(tmp_vec[0], tmp_vec[1], tmp_vec[2]);
				T = T * M;
			} else if (cmd == "rotate") {
				vec4 tmp_vec;
				for (int i = 0; i < 3; ++i) {
					s_stream >> tmp_vec[i];
				}
				float degrees;
				s_stream >> degrees;
				vec3 tmp_axis = glm::normalize(glm::normalize(tmp_vec));
				mat4 T = transfstack.top();
				mat4 M = Transform::rotate(degrees, tmp_vec);
				T = T * M;
			}
		}
	}
}

void Scene::add_light(Light _light) {
	this->light_vector.push_back(_light);
}

void Scene::disLightInfo() {
	std::cout << "Light Num : " << this->light_vector.size() << std::endl;
	std::vector<Light>::iterator itor;
	for (itor = this->light_vector.begin(); itor != this->light_vector.end();++ itor) {
		itor->disInfo();
		std::cout << std::endl;
	}
}

void Scene::disObjectInfo() {
	std::cout << "Object Num : " << this->object_vector.size() << std::endl;
	std::vector<Object*>::iterator itor;
	for (itor = this->object_vector.begin(); itor != this->object_vector.end(); ++itor) {
		(*itor)->disInfo();
		std::cout << std::endl;
	}
}

void Scene::disSceneInfo() {
	std::cout << "Scene Name : " << scene_name << std::endl;
	std::cout << "Scene Size : " << image_width << " x " << image_height << std::endl;
}