#ifndef HANDLE_ERROR_HPP
#define HANDLE_ERROR_HPP

#include "../../shared/Server.hpp"

class HandleError
{
	// порядок этих enum-констант СТРОГО совпадает с массивом имён
	enum ServerVar
	{
		LISTEN,
		SERVER_NAME,
		ERROR_PAGE,
		SERVER_VAR_COUNT
	};

	static const char *const multiplieVarsServer[SERVER_VAR_COUNT];

public:
	// возвращает false, если найдена ошибка
	static bool errorHandler(std::vector<Server> &servers);
};

#endif