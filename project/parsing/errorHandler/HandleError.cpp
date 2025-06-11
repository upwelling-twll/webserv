#include "./HandleError.hpp"
#include <iostream>
#include <cctype>
#include <sstream>

const char *const HandleError::multiplieVarsServer[HandleError::SERVER_VAR_COUNT] = {
	"listen", "server_name", "error_page"};

/* ───────────── LISTEN ───────────── */
bool HandleError::handleListen(Server &srv)
{
	const std::vector<std::string> &values = srv.get("listen");

	if (values.size() != 1)
	{
		std::cerr << "Invalid 'listen' count\n";
		return false;
	}

	const std::string &raw = values[0];
	std::size_t pos = raw.rfind(':');
	if (pos == std::string::npos || pos == 0 || pos + 1 >= raw.size())
	{
		std::cerr << "Invalid 'listen' format\n";
		return false;
	}

	std::string addr = raw.substr(0, pos);
	std::string port = raw.substr(pos + 1);

	if (!std::all_of(port.begin(), port.end(), ::isdigit))
	{
		std::cerr << "Port must be numeric\n";
		return false;
	}

	std::vector<std::string> split;
	split.push_back(addr);
	split.push_back(port);
	srv.reset("listen", split);
	return true;
}

/* ────────── SERVER_NAME ─────────── */
bool HandleError::handleServerName(Server &srv)
{
	const std::vector<std::string> &values = srv.get("server_name");
	if (values.empty())
	{
		std::cerr << "'server_name' must contain at least one name\n";
		return false;
	}

	static const std::regex hostRe("^[A-Za-z0-9.-]+$");
	for (std::size_t i = 0; i < values.size(); ++i)
	{
		if (!std::regex_match(values[i], hostRe))
		{
			std::cerr << "Invalid server_name: " << values[i] << '\n';
			return false;
		}
	}
	return true;
}

/* ─────────── ERROR_PAGE ─────────── */
bool HandleError::handleErrorPage(Server &srv)
{
	const std::vector<std::string> &tokens = srv.get("error_page");

	if (tokens.empty())
		return true;

	const std::string &path = tokens.back();
	if (path.empty() || path[0] != '/')
	{
		std::cerr << "Invalid path in error_page: " << path << '\n';
		return false;
	}

	for (std::size_t i = 0; i + 1 < tokens.size(); ++i)
	{
		const std::string &codeStr = tokens[i];

		if (codeStr.length() != 3 ||
			!std::isdigit(codeStr[0]) ||
			!std::isdigit(codeStr[1]) ||
			!std::isdigit(codeStr[2]))
		{
			std::cerr << "Invalid HTTP status code: " << codeStr << '\n';
			return false;
		}

		int code = std::atoi(codeStr.c_str());
		if (code < 300 || code > 599)
		{
			std::cerr << "Unsupported status code in error_page: " << code << '\n';
			return false;
		}
	}

	return true;
}

/* ───────────── HANDLE ERROR ───────────── */
bool HandleError::errorHandler(std::vector<Server> &servers)
{
	for (std::size_t s = 0; s < servers.size(); ++s)
	{
		Server &srv = servers[s];

		if (!handleListen(srv))
			return false;
		if (!handleServerName(srv))
			return false;
		if (!handleErrorPage(srv))
			return false;
	}
	return true;
}