#pragma once
#ifndef _SH_SCENE_
#define _SH_SCENE_
#include <glm/glm.hpp>
#include <vector>
#include "Object.h"
#include "Camera.h"
class Scene {
private:
	int image_height;
	int image_width;
	int max_ray_depth;
	int scene_name;
	std::vector<Object> object_vector;
	Camera camera;
public:
	Scene() {
	}
	void scene_analyzer(std::vector<std::string>);
};
#endif