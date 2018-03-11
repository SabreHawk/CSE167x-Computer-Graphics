#include "FileManager.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Scene.h"
using namespace std;

int main() {
	glm::vec3 t;
	t[0] = 1;
	t[1] = 2;
	t[2] = 0;
	std::cout << t[0] << std::endl;
	string a = "scene-info/scene5.test";
	FileManager file_manager(a);
	file_manager.read_file();
	
	Scene tmp_scene;
	tmp_scene.scene_analyzer(file_manager.getContent());
	//tmp_scene.light_info();
	cin.get();
}