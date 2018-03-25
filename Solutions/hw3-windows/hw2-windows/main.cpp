#include "FileManager.h"
#include <glm/glm.hpp>
#include "Scene.h"
#include "Transform.h"
#include <algorithm>
using namespace std;
using namespace glm;
int main() {
	bool isTest = false;
	if (isTest) {
		Ray tmp_r(glm::vec3(0, 0,10), glm::vec3(0, 0, -1));
		//Sphere tmp_s(glm::vec3(0,0,0),2);
		//glm::mat4 tmp_m = Transform::translate(0,0,-1)*Transform::scale(2, 2, 2);
		//tmp_s.setTransMat(tmp_m);
		//float tmp_t = tmp_s.intersectRay(tmp_r).getDis();
		//std::cout << "t : " << tmp_t << std::endl;
		//glm::vec3 tmp_p = tmp_r.getOriginPos() + tmp_t * tmp_r.getDirection();
		//std::cout << "Inter Point " << std::endl;
		//for (int i = 0; i < 3; ++i) {
		//	std::cout << tmp_p[i] << " ";
		//}std::cout << std::endl;
		//glm::vec3 ref = tmp_s.getReflectionRay(tmp_r);
		//std::cout << "Normal" << std::endl;
		//for (int i = 0; i < 3; ++i) {
		//	std::cout << tmp_s.getNormal(tmp_p)[i] << " ";
		//}std::cout << std::endl;
		//cin.get();
		glm::vec3 tmp_v[3];
		tmp_v[0] = glm::vec3(-1, -1, 12);
		tmp_v[1] = glm::vec3(1, -1, 12);
		tmp_v[2] = glm::vec3(0, 10, 12);
		Sphere tmp_s(glm::vec3(0,0,0),1);
		glm::mat4 tmp_m = Transform::translate(0, 0, 15)*Transform::scale(3, 3,3);
		tmp_s.setTransMat(tmp_m);
		float tmp_t = tmp_s.intersectRay(tmp_r).getDis();
		if (tmp_s.intersectRay(tmp_r).getIsIns()) {
			std::cout << "t : " << tmp_t << std::endl;
			glm::vec3 tmp_p = tmp_s.intersectRay(tmp_r).getPos();
			std::cout << "Inter Point " << std::endl;
			for (int i = 0; i < 3; ++i) {
				std::cout << tmp_p[i] << " ";
			}std::cout << std::endl;
			std::cout << "Normal" << std::endl;
			for (int i = 0; i < 3; ++i) {
				std::cout << tmp_s.intersectRay(tmp_r).getNormal()[i] << " ";
			}std::cout << std::endl;
			std::cout << "Reflect" << std::endl;
			for (int i = 0; i < 3; ++i) {
				std::cout << tmp_s.getReflectionRay(tmp_r)[i] << " ";
			}std::cout << std::endl;
		} else {
			std::cout << "No Inter" << std::endl;
		}
		
		cin.get();
	} else {
		string amb = "scene-info/scene4-ambient.test";
		string diff = "scene-info/scene4-diffuse.test";
		string emi = "scene-info/scene4-emission.test";
		string spe = "scene-info/scene4-specular.test";
		string s5 = "scene-info/scene5.test";
		string s6 = "scene-info/scene6.test";
		string s7 = "scene-info/scene7.test";
		string test = "scene-info/mytest.test";
		FileManager file_manager(s7);
		file_manager.read_file();
		Scene tmp_scene;
		
		tmp_scene.scene_analyzer(file_manager.getContent());
		//tmp_scene.disObjectInfo();
		tmp_scene.disSceneInfo();
		tmp_scene.render();
		//cin.get();
	}
}