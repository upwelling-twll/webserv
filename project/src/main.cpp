#include <iostream>
#include "../shared/Config.hpp"

Conf initMockConfig()
{
    ServerStruct server_struct;
    Server mockServer(server_struct);
    Port   mockPort("127.0.0.1", 8080);
    std::vector<Server> servs;
    std::vector<Port> ports;
    
    servs.push_back(mockServer);
    ports.push_back(mockPort);
    Config mockConf(servs, ports);
    return (mockConf);
}

int main()
{
    Config newConf() = initMockConfig();


    return (1);
}