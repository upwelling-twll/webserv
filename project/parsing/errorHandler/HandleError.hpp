#ifndef HANDLE_ERROR_HPP
#define HANDLE_ERROR_HPP

#include "../../shared/Server.hpp"
#include <vector>
#include <string>
#include <regex>

class HandleError
{
	enum ServerVar
	{
		LISTEN,
		SERVER_NAME,
		ERROR_PAGE,
		SERVER_VAR_COUNT
	};

	static const char *const multiplieVarsServer[SERVER_VAR_COUNT];

	static bool handleListen(Server &srv);
	static bool handleServerName(Server &srv);
	static bool handleErrorPage(Server &srv);

public:
	static bool errorHandler(std::vector<Server> &servers);
};

#endif