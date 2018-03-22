#include "FileManager.h"
#include <glm/glm.hpp>
#include "Scene.h"
#include <algorithm>
using namespace std;

int main() {
	bool isTest = false;
	if (isTest) {
		glm::vec3 tmp_v_a[3] = { {1,1,0},{0,1,1},{1,0,1} };
		Ray tmp_r(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
		Triangle t(tmp_v_a);
		std::cout << t.intersectRay(tmp_r) << std::endl;
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