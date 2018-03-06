//Implement Scene.h

#include <sstream>
#include "Scene.h"
#include "light.h"
Scene::Scene() {
}

void Scene::scene_analyzer(std::vector<std::string> _content) {
	std::vector<std::string>::iterator itor;
	std::string tmp_str;
	std::string cmd;
	for (itor = _content.begin(); itor != _content.end(); ++itor) {
		tmp_str = *itor;

		if ((tmp_str.find_first_not_of(" \t\r\n") != std::string::npos) && (tmp_str[0] != '#')) {
			std::stringstream s_stream(tmp_str);
			s_stream >> cmd;
			if (cmd == "light") {
				Light
			}
		}
	}
}