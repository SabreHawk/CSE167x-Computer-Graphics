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
#include <fstream>
//

//
void Scene::savePic() {
	FIBITMAP *img = FreeImage_ConvertFromRawBits(image_mat, this->image_width, this->image_height, this->image_width * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, true);
	std::cout << "Saving Screenshot : " << this->scene_name.c_str() << "\n";
	FreeImage_Save(FIF_PNG, img, this->scene_name.c_str(), 0);
}

glm::vec3 Scene::traceRay(Ray _r,int _layer) {
	if (_layer >= this->max_ray_depth) {
		return glm::vec3(0);
	}
	//Find Nearest Object 
	std::vector<Object*>::iterator itor;
	std::vector<Object*>::iterator nearest_itor;
	float min_dis = INFINITY;
	glm::vec3 tmp_pos;
	IntersectionInfo tmp_ins_info;
	IntersectionInfo final_ins_info;
	for (itor = this->object_vector.begin(); itor != this->object_vector.end(); ++itor) {
			tmp_ins_info = (*itor)->intersectRay(_r);
		if (tmp_ins_info.getIsIns() == false) {//No Interesction
			continue;
		} else if (tmp_ins_info.getDis() < min_dis &&  tmp_ins_info.getDis()>0.00001f) {
			min_dis = tmp_ins_info.getDis();
			final_ins_info = tmp_ins_info;
			nearest_itor = itor;
		}
	}
	if (min_dis == INFINITY) {
		return glm::vec3(0);
	}
	if (min_dis < 0) {
		std::cout << "A";
	}
	tmp_pos = final_ins_info.getPos();
	
	//Render Object 
	glm::vec3 layer_color = (*nearest_itor)->getAmbient() + (*nearest_itor)->getEmission();
	std::vector<Light>::iterator light_itor;
	glm::vec3 tmp_light_dir;
	glm::vec3 tmp_eye_dir;
	for (light_itor = this->light_vector.begin(); light_itor != this->light_vector.end(); ++light_itor) {
		float i = 1;
		if (light_itor->getType() == 1) {
			i = 1 / light_itor->computeDecy(glm::length(light_itor->getPos() - tmp_pos), this->attenuation);
			tmp_light_dir = glm::normalize(light_itor->getPos() - final_ins_info.getPos());
		} else {
			tmp_light_dir = glm::normalize((light_itor->getPos()));
		}
		if (!isVisToLight(final_ins_info.getPos(), *light_itor)) {
			continue;
		}

		tmp_eye_dir = glm::normalize(_r.getOriginPos() - final_ins_info.getPos());
		layer_color += i * ((*nearest_itor)->computeLambertLight(tmp_light_dir, final_ins_info.getNormal(), *light_itor) + (*nearest_itor)->computePhongLight(tmp_light_dir, tmp_eye_dir, final_ins_info.getNormal(), *light_itor));
	}
	Ray next_ray(tmp_pos, (*nearest_itor)->getReflectionRay(_r));
	return   (layer_color)+(*nearest_itor)->getSpecular() * traceRay(next_ray, _layer + 1);
}

Ray Scene::genRay(int _i, int _j) {
	float aspect = this->image_width / (float)this->image_height;
	glm::vec3 alpha = this->camera.getU()* (glm::tan(this->camera.getFovY()*pi / 180 / 2)*aspect*(float(_j + 0.5) - this->image_width / 2) / (this->image_width / 2));
	glm::vec3 beta = this->camera.getV() * (glm::tan(this->camera.getFovY()*pi / 180 / 2)*(this->image_height / 2 - float(_i + 0.5)) / (this->image_height/2));
	glm::vec3 neg_gama = float(-1) * this->camera.getW();
	//std::cout << "Camera" << std::endl;
	//for (int i = 0; i < 3; ++i) {
	//	//std::cout << this->get[i] << " ";
	//}std::cout << std::endl;
	glm::vec3 dir = glm::normalize(alpha + beta + neg_gama);
	return Ray(this->camera.getCameraPos(), dir);
}

Scene::Scene(int _h, int _w, int _d, std::string _n)
	:image_height(_h), image_width(_w), max_ray_depth(_d), scene_name(_n) {
	this->image_mat = new BYTE[3 * _h * _d];
	this->max_ray_depth = 5;
	this->attenuation = glm::vec3(1, 0, 0);
}

Scene::Scene() {
	this->max_ray_depth = 5;
	this->attenuation = glm::vec3(1, 0, 0);
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
	glm::vec3 tmp_attenuation(1, 0, 0);
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
					s_stream >> float(tmp_ambient[i]);
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
			} else if (cmd == "attenuation") {
				for (int i = 0; i < 3; ++i) {
					s_stream >> this->attenuation[i];
				}
			} else if (cmd == "size") {
				s_stream >> this->image_width;
				s_stream >> this->image_height;
				this->image_mat = new BYTE[3 * this->image_width * this->image_height];
			} else if (cmd == "output") {
				s_stream >> this->scene_name;
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
					glm::vec4 tmp_pp = transfstack.top()*glm::vec4(vertex_vec[int(tmp_vec[i])], 1);
					tmp_vertexs[i] = glm::vec3(tmp_pp.x / tmp_pp.w, tmp_pp.y / tmp_pp.w, tmp_pp.z / tmp_pp.w);
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
				mat4 &T = transfstack.top();
				mat4 M = mat4(Transform::rotate(degrees, tmp_vec));
				T = T * M;
			} else if (cmd == "maxdepth") {
				s_stream >> this->max_ray_depth;
			}
		}
	}
}

void Scene::add_light(Light _light) {
	this->light_vector.push_back(_light);
}

void Scene::render() {
	std::ofstream outfile("im.txt");
	int pixel_counter = 0;
	for (int i = 0; i < this->image_height; ++i) {
		for (int j = 0; j < this->image_width; ++j) {
			Ray tmp_ray = this->genRay(i, j);
			glm::vec3 tmp_color = this->traceRay(tmp_ray, 0);
			for (int k = 0; k < 3; ++k) {
				this->image_mat[pixel_counter * 3 + k] = float(tmp_color[2-k]) * 255;
				outfile << float(tmp_color[k]) << " ";
			}outfile << std::endl;
			pixel_counter++;
		}
		if(pixel_counter%300==0){
			std::cout << "Percentage : " << pixel_counter * 100 / (this->image_height*this->image_width) << "%\r";
		}
		
	}
	outfile.close();
	savePic();
}

int Scene::isVisToLight(glm::vec3 _p, Light & _l) {
	Ray tmp_r(_p, glm::normalize(_l.getPos() - _p));
	std::vector<Object*>::iterator itor;
	IntersectionInfo tmp_ins_info;
	for (itor = this->object_vector.begin(); itor != this->object_vector.end(); ++itor) {
		tmp_ins_info = (*itor)->intersectRay(tmp_r);
		if (tmp_ins_info.getIsIns() == true) {// Interesction
			float pToLightDis;
			if (_l.getType() == 1) {
				pToLightDis = glm::length(_l.getPos() - _p);
			} else {
				return 0;
			}

			float pToObjectDis = tmp_ins_info.getDis();
			if (pToLightDis > pToObjectDis) {
				return 0;
			}
		}
	}
	return 1;
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