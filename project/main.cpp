#include <iostream>
#include "inc/webserv.hpp"

int main(int argc, char** argv)
{
	if (argc != 2)
		return 1;
	const char* file = argv[1];

	std::vector<ServerParse> server_vector;
	try
	{
		Parser parser(file, server_vector);
		// HandleError::errorHandler(server_vector);
		for(int i = 0; i < (int)server_vector.size(); i++){
			server_vector[i].print();
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	}
	
	std::vector<Server> servers;
	for (std::vector<ServerParse>::iterator it = server_vector.begin(); it != server_vector.end(); ++it)
	{
		Server server(*it); // Create a Server object from the ServerParse object
		servers.push_back(server);
	}
	Config newConf(servers); //constructor using Servers vector and creating a Locations vector during the construction

	std::cout << "Data for config is created" << std::endl;
    try
	{
		newConf.startWebServ();
	}
	catch(const std::exception& e)
	{
		std::cout << "Server start impossible" << std::endl;
	}
	//TODO : for each IP:PORT check that the is running deamon of this server 
	Engine	engine(newConf.getAllSockets());

	if (!engine.engineRoutine(newConf))
	{
		std::cout << "Error: engin failed" << std::endl;
	}

	newConf.closeAllFds();
	return (1);
}