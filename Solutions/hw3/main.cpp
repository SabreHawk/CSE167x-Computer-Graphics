#include "FileManager.h"
using namespace std;
#include <GL/glew.h>
#include <GL/glut.h>

int main(){
    string a= "scene5.test";
    FileManager file_manager(a);
    file_manager.read_file();
    file_manager.print_content();

}