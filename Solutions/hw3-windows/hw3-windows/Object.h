#ifndef _SH_Object_
#define _SH_Object_
#include <string>
#include <glm/glm.hpp>
class Object{
private:
    std::string type;
    float size ;
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	glm::vec4 emission;
	float shininess ;
	glm::mat4 transform ; 
public:
	Object();
	void setType(std::string);
	void setAmbient(glm::vec4);
	void setDiffuse(glm::vec4);
	void setSpecular(glm::vec4);
	void setEmission(glm::vec4);
};

#endif
