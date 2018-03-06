#include "FileManager.h"

FileManager::FileManager(){
}
FileManager::FileManager(std::string _file_name){
    file_name = _file_name;
}

void FileManager::add_line(std::string _line){
    content.push_back(_line);
}
void FileManager::add_line(std::string _line, int _line_index){
    content.insert(content.begin()+_line_index,_line);
}
void FileManager::read_file(){
    std::ifstream in_stream(file_name.c_str());
    std::string tmp_line;
    if (in_stream){
        while(getline(in_stream,tmp_line)){
                add_line(tmp_line);
        }
    }else{
        std::cout << "ERROR : No File Named <" <<file_name<<">" <<std::endl;
    }
}

void FileManager::print_content(){
        std::vector<std::string>::iterator itor;
		int i = 0;
		std::cout << content.size() << std::endl;
        for(itor = content.begin(); itor != content.end();++ itor){
            std::cout << *itor << std::endl;
        }
}
void FileManager::print_content(int _index) {
	std::cout << content[_index] << std::endl;
}