#include <iostream>
#include "inc/webserv.hpp"

Config initMockConfig()
{
	std::cout << "Mock server 1" << std::endl;
    Server					mockServer;
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
	Server					mockServer2;
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

int main()
{
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
	if (!connectClients(newConf))
	{
		std::cout << "Error: failed connecting clients" << std::endl;
	}
	return (1);
}