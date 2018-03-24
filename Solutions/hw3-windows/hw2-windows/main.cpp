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
		Ray tmp_r(glm::vec3(0, 0, 5), glm::vec3(0, 0, -1));
		Sphere tmp_s(glm::vec3(0,0,0),2);
		glm::mat4 tmp_m = Transform::translate(0,0,-1)*Transform::scale(2, 2, 2);
		tmp_s.setTransMat(tmp_m);
		float tmp_t = tmp_s.intersectRay(tmp_r);
		std::cout << "t : " << tmp_t << std::endl;
		glm::vec3 tmp_p = tmp_r.getOriginPos() + tmp_t * tmp_r.getDirection();
		std::cout << "Inter Point " << std::endl;
		for (int i = 0; i < 3; ++i) {
			std::cout << tmp_p[i] << " ";
		}std::cout << std::endl;
		glm::vec3 ref = tmp_s.getReflectionRay(tmp_r);
		std::cout << "ref dir " << std::endl;
		for (int i = 0; i < 3; ++i) {
			std::cout << ref[i] << " ";
		}std::cout << std::endl;
		cin.get();
	} else {
		string a = "scene-info/scene4-ambient.test";
		FileManager file_manager(a);
		file_manager.read_file();

		Scene tmp_scene;
		tmp_scene.scene_analyzer(file_manager.getContent());
		//tmp_scene.disObjectInfo();
		tmp_scene.render();
		cin.get();
	}
}