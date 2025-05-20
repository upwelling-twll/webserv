#include "./HandleError.hpp"
#include <cstring>
#include <iostream>

const char *const HandleError::multiplieVarsServer[HandleError::SERVER_VAR_COUNT] = {
	"listen", "server_name", "error_page"};

bool HandleError::errorHandler(std::vector<Server> &servers)
{
	for (std::size_t s = 0; s < servers.size(); ++s)
	{
		Server &srv = servers[s];

		for (int i = 0; i < SERVER_VAR_COUNT; ++i)
		{
			const std::vector<std::string> &values = srv.get(multiplieVarsServer[i]);

			switch (static_cast<ServerVar>(i))
			{
			case LISTEN:
			{
				if (srv.get("listen").size() != 1)
				{
					std::cout << "Size is: " << srv.get("listen").size() << std::endl;
					std::cout << "Invalid 'listen' count: ";
					for (size_t k = 0; k < srv.get("listen").size(); k++)
					{
						std::cout << " |" << srv.get("listen")[k] << "| ";
					}
					std::cout << std::endl;
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

				for (std::size_t k = 0; k < port.size(); ++k)
					if (!std::isdigit(static_cast<unsigned char>(port[k])))
					{
						std::cerr << "Port must be numeric\n";
						return false;
					}

				std::vector<std::string> split;
				split.push_back(addr);
				split.push_back(port);

				srv.reset("listen", split);
				break;
			}

			case SERVER_NAME:
				break;

			case ERROR_PAGE:
				break;

			default:
				break;
			}
		}
	}
	return true;
}