#include "./Parser.hpp"

Parser::Parser(const char *filename){
	std::ifstream file;
	std::string line;
	file.open(filename);
	std::getline(file, line);
	std::cout << "The Line: "<< line << std::endl;
	
}