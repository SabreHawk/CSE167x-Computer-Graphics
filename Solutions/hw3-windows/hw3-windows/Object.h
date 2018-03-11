#ifndef _SH_Object_
#define _SH_Object_
#include <string>
#include <glm/glm.hpp>
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
	glm::mat4 getTransMat();
	virtual void disInfo();
	virtual void transObject();
};

class Sphere : public Object {
private:
	glm::vec3 center_pos;
	float radius;
public:
	Sphere();
	Sphere(glm::vec3, float);
	void disInfo();
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
};
#endif
