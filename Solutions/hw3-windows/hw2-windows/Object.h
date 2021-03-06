#ifndef _SH_Object_
#define _SH_Object_
#include <string>
#include <glm/glm.hpp>
#include "Ray.h"
#include "Light.h"
#include "IntersectionInfo.h"

class Object{
private:
    std::string type;
    float size ;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 emission;
	float shininess ;
	glm::mat4 transform ; 
public:
	Object();
	void setType(std::string);
	void setAmbient(glm::vec3);
	void setDiffuse(glm::vec3);
	void setSpecular(glm::vec3);
	void setEmission(glm::vec3);
	void setShininess(float);
	void setTransMat(glm::mat4);
	virtual std::string getType();
	virtual glm::vec3 getAmbient();
	virtual glm::vec3 getDiffuse();
	virtual glm::vec3 getSpecular();
	virtual glm::vec3 getEmission();
	virtual glm::vec3 getNormal(glm::vec3=glm::vec3(0)) = 0;
	virtual float getShininess();
	virtual glm::mat4 getTransMat();
	virtual void transObject() = 0;
	virtual IntersectionInfo intersectRay(Ray &) = 0;
	virtual IntersectionInfo shadowIntersection(Ray &) = 0;
	virtual glm::vec3 computeLambertLight(glm::vec3 &, glm::vec3 &, Light &) = 0;
	virtual glm::vec3 computePhongLight(glm::vec3 &, glm::vec3 &, glm::vec3 &, Light &) = 0;
	virtual void disInfo();
	virtual glm::vec3 getReflectionRay(Ray &) = 0;
};

class Sphere : public Object {
private:
	glm::vec3 center_pos;
	float radius;
public:
	Sphere();
	Sphere(glm::vec3, float);
	void disInfo();
	IntersectionInfo intersectRay(Ray &);
	IntersectionInfo shadowIntersection(Ray &);
	void transObject();
	glm::vec3 getNormal(glm::vec3);
	glm::vec3 computeLambertLight(glm::vec3 &, glm::vec3 &, Light &);
	glm::vec3 computePhongLight(glm::vec3 &, glm::vec3 &, glm::vec3 &, Light &);
	glm::vec3 getReflectionRay(Ray &);
};

class Triangle :public Object {
private:
	glm::vec3 vertexs[3];
	glm::vec3 normal;
public:
	Triangle();
	Triangle(glm::vec3 _v[3]);
	void disInfo();
	void transObject();
	void setTransMat(glm::mat4 _m);
	IntersectionInfo intersectRay(Ray &); 
	IntersectionInfo shadowIntersection(Ray &);
	glm::vec3 computeLambertLight(glm::vec3 &, glm::vec3 &, Light &);
	glm::vec3 computePhongLight(glm::vec3 &, glm::vec3 &, glm::vec3 &, Light &);
	glm::vec3 getReflectionRay(Ray &);
	glm::vec3 getNormal(glm::vec3=glm::vec3(0));
};
#endif

