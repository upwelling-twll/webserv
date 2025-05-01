#include <iostream>
#include "shared/Config.hpp"

Config initMockConfig()
{
    Server		mockServer;
	Location	mockLocation;
    Port   		mockPort("127.0.0.1", 8080);
	std::vector<Location>	locs;
    std::vector<Server> servs;
    std::vector<Port> ports;
    
	locs.push_back(mockLocation);
	mockServer.addLocation(locs);
    servs.push_back(mockServer);
    ports.push_back(mockPort);
    Config mockConf(servs, ports);
    return (mockConf);
}

int main()
{
    Config newConf = initMockConfig();

	std::cout << "Data for Mock config is created" << std::endl;
    newConf.startWebServ();
	return (1);
}