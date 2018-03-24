#pragma once
#ifndef _SH_SCENE_
#define _SH_SCENE_
#include <glm/glm.hpp>
#include <FreeImage.h>
#include <vector>
#include "Object.h"
#include "Camera.h"
#include "Light.h"
class Scene {
private:
	//Params
	int image_height;
	int image_width;
	int max_ray_depth;
	std::string scene_name;
	std::vector<Light> light_vector;
	std::vector<Object*> object_vector;
	glm::vec3 attenuation;
	Camera camera;
	BYTE * image_mat;
	//Method
	glm::vec3 traceRay(Ray,int);
	Ray genRay(int, int);
public:
	Scene(int, int, int, std::string);
	Scene();
	void scene_analyzer(std::vector<std::string>);
	void add_light(Light);
	void render();
	void savePic();
	void disLightInfo();
	void disObjectInfo();
	void disSceneInfo();
};
#endif