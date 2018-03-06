#ifndef _SH_Object_
#define _SH_Object_
#include <string>
#include <glm/glm.hpp>
class Object{
private:
    std::string type;
    float size ;
    float ambient[4] ; 
    float diffuse[4] ; 
    float specular[4] ;
    float emission[4] ; 
    float shininess ;
  mat4 transform ; 

};
#endif
