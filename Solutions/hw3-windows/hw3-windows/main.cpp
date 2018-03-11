#include "FileManager.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Scene.h"
using namespace std;

int main() {
	bool isTest = false;
	if (isTest) {
		/*glm::vec4 tmp(1,2,2,1);
		glm::vec3 a;*/
		//a = glm::vec3(tmp);
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