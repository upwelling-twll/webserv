#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <list>

# include "../shared/Config.hpp"
# include "../src/core/Socket.hpp"
# include "../src/core/Engine.hpp"


void addPortsToSocketsList(std::vector<Socket> allSockets, std::vector<Port> ports);
std::vector<Socket> createSocketVec(Config config);

#endif