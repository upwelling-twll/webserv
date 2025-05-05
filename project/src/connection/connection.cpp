#include "../../inc/webserv.hpp"

int connectClients(Config config)
{
   std::vector<Port> ports = config.getPorts();
   
    for (std::vector<Port>::iterator it = ports.begin(); it != ports.end(); ++it)
    {
        std::cout << "hi" << std::endl;
    }
    return (false);
}