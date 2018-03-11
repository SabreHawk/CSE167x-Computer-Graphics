#include "FileManager.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Scene.h"
using namespace std;

int main() {
	bool isTest = true;
	if (isTest) {
		glm::vec3 tmp;
		if (&tmp == nullptr) {
			cout << "s" << std::endl;
		} else {
			cout << "a" << endl;
		}
			 
		cin.get();
	} else {
		string a = "scene-info/scene4-ambient.test";
		FileManager file_manager(a);
		file_manager.read_file();

		Scene tmp_scene;
		tmp_scene.scene_analyzer(file_manager.getContent());
		/*tmp_scene.disLightInfo();
		tmp_scene.disObjectInfo();*/
		tmp_scene.disSceneInfo();
		cin.get();
	}
	
}