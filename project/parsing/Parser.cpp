#include "./Parser.hpp"

Parser::Parser(const char *filename){
	std::ifstream file;
	std::string line;
	file.open(filename);
	//while(std::getline(file, line)){
	//	std::cout << "The Line: "<< line << std::endl;

	//}
	std::getline(file, line);
	std::cout << FindChar(line, '{') << std::endl;
	file.close();
}