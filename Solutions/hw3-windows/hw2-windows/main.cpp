#include "FileManager.h"
#include <glm/glm.hpp>
#include "Scene.h"
#include <algorithm>
using namespace std;
using namespace glm;
int main() {
	bool isTest = true;
	if (isTest) {
		glm::vec3 tmp_v_a[3] = { {1,1,0},{0,1,1},{1,0,1} };
		Ray tmp_r(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
		Triangle t(tmp_v_a);
		glm::vec3 n = t.getNormal();

		//Ray tmp_n = t.getReflectionRay(tmp_r);
		std::cout << t.intersectRay(tmp_r) << std::endl;
		glm::vec3 tmp_p = tmp_r.getOriginPos() + t.intersectRay(tmp_r)*tmp_r.getDirection();

		for (int i = 0; i < 3; ++i) {
			std::cout << tmp_p[i] << std::endl;
		}
		//
		vec3 AT = vec3(1,1,0);
		vec3 BT = vec3(0,1,1);
		vec3 CT = vec3(1,0,1);
		vec3 abT = BT - AT;
		vec3 acT = CT - AT;
		vec3 normalC = glm::normalize(cross(abT, acT));
		float tt = (dot(AT, normalC) - dot(tmp_r.getOriginPos(), normalC)) / (dot(tmp_r.getDirection(), normalC));
		std::cout << tt << std::endl;
		cin.get();
	} else {
		string a = "scene-info/mytest.test";
		FileManager file_manager(a);
		file_manager.read_file();

		Scene tmp_scene;
		tmp_scene.scene_analyzer(file_manager.getContent());
		//tmp_scene.disObjectInfo();
		tmp_scene.render();
		cin.get();
	}
}