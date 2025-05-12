#include "Engine.hpp"

/*Member functions*/
int Engine::engineRoutine(Config config)
{
	(void)config;

	std::vector<struct pollfd> fds;

	std::cout << "	Engine routine is called" << std::endl;
	for (std::vector<Socket>::iterator it = _allSockets.begin(); it != _allSockets.end(); ++it)
	{
		fds.push_back({it, POLLIN, 0}) 
	}
	int maxFd = _allSockets.back().getFd();
	while(true)
	{
		//timeout=0, then poll() will return without blocking.
		int n = poll(fds.data(), fds.size(), 0);
		if (n < 0)
		{
			perror("poll");
			continue;
		}
		for (size_t i = 0; i < fds.size(); i++)
		{
			if (fds.[i].revents && POLLIN)
			{
				if (is_listening_socket(fds[i].fd)) //	acceptNewClients(_allSockets);
				{
					int new_client = accept(fds[i].fd, &addr, sizeof(addr));
					fds.push_back(new_client, POLLIN, 0);
				}
				else
					receiveFromClients(allSockets);
			}
			if (haveResponse(fds[i]))
				sendToClients(allSockets);
		}
	}
	return (0);
}

/*Getters and Setters*/

/*Constructors*/
Engine::Engine(std::vector<Socket> allSockets) : _allSockets(allSockets)
{
   std::cout << "Engine parameterized constructor is called" << std::endl;
}

/*Destructors*/
Engine::~Engine( void )
{
    std::cout << "Engine destructor is called" << std::endl;
}

/*Overload operators*/
Engine& Engine::operator=(const Engine& src)
{
	std::cout << "Engine copy assignment is called" << std::endl;
	if (this != &src)
	{
		this->_allSockets = src._allSockets;
	}
	return (*this);
}

// std::ostream& operator<<(std::ostream& output_stream, Engine& src)
// {
// 	output_stream << "* Engine Class info*" << std::endl;
// 	return output_stream;
// }

