#include <iostream>
#include "../shared/Config.hpp "

Config initStubConfig()
{
	std::vector<Server> servers;
	std::vector<Port> ports;

	
	// Initialize servers and ports with dummy data
	servers.push_back(Server("127.0.0.1", 8080));
	
}

int main()
{
	Config newConfig() = initStubConfig();

	newConfig.configureServers();
	return (0);
}