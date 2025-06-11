
#include <iostream>
#include "./parsing/Parser.hpp"
#include "./parsing/errorHandler/HandleError.hpp"

int main(int argc, char** argv)
{
	if (argc != 2)
		return 1;
	const char* file = argv[1];

	try {
		std::vector<Server> server_vector;
		Parser parser(file, server_vector);
		HandleError::errorHandler(server_vector);
		for(int i = 0; i < (int)server_vector.size(); i++){
			server_vector[i].print();
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	}
	return 0;
}