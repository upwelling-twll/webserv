#include <iostream>
#include "inc/webserv.hpp"

Config initMockConfig()
{
	std::cout << "Mock server 1" << std::endl;
    Server					mockServer("127.0.0.1", 8080);
	Location				mockLocation;
    Port   					mockPort("127.0.0.1", 8080);
	std::vector<Location>	locs;
    std::vector<Server> 	servs;
    std::vector<Port>		ports;

	locs.push_back(mockLocation);
	mockServer.addLocation(locs);
    servs.push_back(mockServer);
    ports.push_back(mockPort);

	std::cout << "Mock server 2" << std::endl;
	Server					mockServer2("127.0.0.1", 1025);
	Location				mockLocation2;
    Port   					mockPort2("127.0.0.1", 1025);
	std::vector<Location>	locs2;

	locs2.push_back(mockLocation2);
	mockServer2.addLocation(locs2);

    servs.push_back(mockServer2);
    ports.push_back(mockPort2);
	
	std::cout << "\nCreating config instance" << std::endl;
    Config mockConf(servs, ports);
    return (mockConf);
}

int main(int argc, char** argv)
{
	if (argc != 2)
		return 1;
	const char* file = argv[1];

	try
	{
		std::vector<ServerParse> server_vector;
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

    Config newConf = initMockConfig();

	std::cout << "Data for Mock config is created" << std::endl;
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