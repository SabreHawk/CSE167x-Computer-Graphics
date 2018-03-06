#include "FileManager.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
using namespace std;

int main() {
	string a = "scene-info/scene5.test";
	FileManager file_manager(a);
	file_manager.read_file();
	file_manager.print_content(2);
	cin.get();
}