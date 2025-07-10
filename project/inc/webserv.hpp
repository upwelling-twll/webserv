#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <sys/socket.h>
# include <vector>
# include <iostream>
# include <map>

# include "../shared/Config.hpp"
# include "../shared/Server.hpp"
# include "../shared/ServerParse.hpp"
# include "../shared/Port.hpp"
# include "../src/core/Socket.hpp"
# include "../src/core/ListeningSocket.hpp"
# include "../src/core/ConnectionSocket.hpp"
# include "../src/core/Engine.hpp"
# include "../src/core/Connection.hpp"
# include "../src/http/AHttpRequest.hpp"
# include "../parsing/Parser.hpp"
# include "../utils/SocketIO.hpp"


void                    addPortsToSocketsList(std::vector<Socket>& allSockets, std::vector<Port> ports);
std::vector<Socket*>    createSocketVec(Config config);
bool                    locateSymbol(const std::string& string, char symbol);

#endif