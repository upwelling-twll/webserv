#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <sys/socket.h>
# include <list>

# include "../shared/Config.hpp"
# include "../shared/Server.hpp"
# include "../shared/Port.hpp"
# include "../src/core/Socket.hpp"
# include "../src/core/ListeningSocket.hpp"
# include "../src/core/ConnectionSocket.hpp"
# include "../src/core/Engine.hpp"


void                addPortsToSocketsList(std::vector<Socket>& allSockets, std::vector<Port> ports);
std::vector<Socket> createSocketVec(Config config);

#endif