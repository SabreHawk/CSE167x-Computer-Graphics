#ifndef _SH_FILE_MANAGER_
#define _SH_FILE_MANAGER_
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
class FileManager{
private:
	std::string file_name;
	std::vector<std::string> content;
public:
    FileManager();
    FileManager(std::string);
    void add_line(std::string);
    void add_line(std::string,int);
    void read_file();
    void print_content();
	void print_content(int);
	std::vector<std::string> getContent();
};

#endif