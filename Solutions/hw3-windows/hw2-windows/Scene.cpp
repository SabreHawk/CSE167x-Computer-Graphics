//Implement Scene.h

#include <sstream>
#include "Scene.h"
#include "Light.h"
#include "Camera.h"
#include "Transform.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <stack>
#include <iostream>

void Scene::savePic() {
	FIBITMAP *img = FreeImage_ConvertFromRawBits(image_mat, this->image_width, this->image_height, this->image_width * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, true);
	std::cout << "Saving Screenshot : " << this->scene_name.c_str() << "\n";
	FreeImage_Save(FIF_PNG, img, this->scene_name.c_str(), 0);
}

glm::vec3 Scene::traceRay(Ray _r,int _layer) {
	if (_layer > 5) {
		return glm::vec3(0);
	}
	std::vector<Object*>::iterator itor;
	std::vector<Object*>::iterator nearest_itor;
	float min_dis = -1;
	float tmp_t;
	glm::vec3 tmp_pos;
	//Find the nearest intersected object;
	for (itor = this->object_vector.begin(); itor != this->object_vector.end(); ++itor) {
		if ((*itor)->getType() == "Sphere") {
			tmp_t = (*itor)->intersectRay(_r);
		} else if ((*itor)->getType() == "Triangle") {
			tmp_t = (*itor)->intersectRay(_r);
		}
		if (tmp_t == -1) {//No Interesction
			continue;
		} else if (min_dis == -1 || tmp_t < min_dis) {
			min_dis = tmp_t;
			nearest_itor = itor;
		}
	}
	if (min_dis == -1) {
		return glm::vec3(0);
	}
	tmp_pos = _r.getDirection() + tmp_t * _r.getOriginPos();
	Ray next_ray(tmp_pos, (*nearest_itor)->getReflectionRay(_r));
	glm::vec3 layer_color = (*nearest_itor)->getAmbient() + (*nearest_itor)->getEmission();
	std::vector<Light>::iterator light_itor;
	for (light_itor = this->light_vector.begin(); light_itor != this->light_vector.end(); ++itor) {
		layer_color += (*itor)->computeLambertLight(tmp_pos, *light_itor) + (*itor)->computePhongLight(tmp_pos, *light_itor, _r);
	}

	return layer_color + traceRay(next_ray, _layer + 1);
}

Ray Scene::genRay(int _i, int _j) {
	float fovx = this->camera.getFovX(this->image_width, this->image_height);
	glm::vec3 alpha = this->camera.getU()* (glm::tan(fovx / 2)*(_j - this->image_width / 2) / (this->image_width / 2));
	glm::vec3 beta = this->camera.getV() * (glm::tan(this->camera.getFovY() / 2)*(this->image_height / 2 - _i) / this->image_width);
	glm::vec3 neg_gama = this->camera.getW();
	glm::vec3 dir = glm::normalize(alpha + beta + neg_gama);
	return Ray(this->camera.getCameraPos(), dir);
}

Scene::Scene(int _h, int _w, int _d, std::string _n)
	:image_height(_h), image_width(_w), max_ray_depth(_d), scene_name(_n) {
	this->image_mat = new BYTE[3 * _h * _d];
}

Scene::Scene() {
}

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
	std::stringstream s_stream;
	int a = 0;
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
				Light tmp_light(1, tmp_pos, tmp_color);
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
			Sphere * tmp_sphere = new Sphere(tmp_pos, tmp_radius);
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
			glm::vec3 tmp_vec;
			for (int i = 0; i < 3; ++i) {
				s_stream >> tmp_vec[i];
			}
			glm::vec3 tmp_vertexs[3];
			for (int i = 0; i < 3; ++i) {
				tmp_vertexs[i] = vertex_vec[int(tmp_vec[i])];
				
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
			if (transfstack.size() < 1) {
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
			vec3 tmp_vec;
			for (int i = 0; i < 3; ++i) {
				s_stream >> tmp_vec[i];
			}
			float degrees;
			s_stream >> degrees;
			vec3 tmp_axis = glm::normalize(glm::normalize(tmp_vec));
			mat4 T = transfstack.top();
			mat4 M = mat4(Transform::rotate(degrees, tmp_vec));
			T = T * M;
		} else if (cmd == "camera") {

		}
	}
}

void Scene::add_light(Light _light) {
	this->light_vector.push_back(_light);
}

void Scene::render() {
	for (int i = 0; i < this->image_width; ++i) {
		for (int j = 0; j < this->image_height; ++j) {
			Ray tmp_ray = this->genRay(i, j);
			glm::vec3 tmp_color = this->traceRay(tmp_ray, 0);
			for (int k = 0; k < 3; ++k) {
				this->image_mat[this->image_width * i + j + k] = BYTE(tmp_color[k] * 255);
			}
		}
	}
	savePic();
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