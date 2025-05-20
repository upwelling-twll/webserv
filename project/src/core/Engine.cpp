#include "Engine.hpp"

/*Member functions*/
struct pollfd createNewFd(int _fd, short events, short revents)
{
	struct pollfd newFd;
	
	newFd.fd = _fd;
	newFd.events = events;
	newFd.revents = revents;
	return(newFd);
}

bool	haveResponse(struct pollfd fd)
{
	// std::cout << "	Need to check my response" << std::endl;
	if (fd.fd)
		return (true);
	return (false);
}

bool	sendToClients()
{
	// std::cout << "	Giving my response to the client" << std::endl;
	return (false);
}

int Engine::engineRoutine(Config& config)
{
	(void)config;

	std::vector<struct pollfd> fds;

	std::cout << "	Engine routine is called" << std::endl;
	int s = 0;
	for (std::vector<Socket*>::iterator it = _allSockets.begin(); it != _allSockets.end(); ++it)
	{
		fds.push_back(createNewFd((*it)->getFd(), POLLIN, 0));
		s++;
	}
	std::cout << "	s= " << s << std::endl;
	// int maxFd = _allSockets.back().getFd();
	while(true)
	{
		//timeout=0, then poll() will return without blocking.
		int n = poll(fds.data(), fds.size(), 0);
		if (n < 0)
		{
			perror("poll");
			continue;
		}
	// 	int f = 0;
	// 	for (std::vector<struct pollfd>::iterator it =fds.begin(); it != fds.end(); ++it)
	// 	{
	// 		f++;
	// 	}
	// // 	// std::cout << "	fds= " << f << std::endl;
		// std::cout << "	waiting here" << std::endl;
		for (size_t i = 0; i < fds.size(); i++)
		{
			// std::cout << "	checking fds" << std::endl;
			if (fds[i].revents & POLLIN)
			{
				std::cout << "Have event on socket(fd=" << fds[i].fd << ")" << std::endl; 
				if (_allSockets[i]->isListening())
				{
					struct sockaddr addr;
					socklen_t	size = sizeof(addr);
					int new_client = accept(fds[i].fd, &addr, &size);
					fds.push_back(createNewFd(new_client, POLLIN, 0));
					_allSockets.push_back(new ConnectionSocket(new_client));
				}
				else
				{
					std::cout <<"receiveFromClients" << std::endl;
					allSockets[i]->receiveFromClients();
				}
			}
		}
		// if (haveResponse(fds[i]))
		// 	sendToClients();
		// 	// else
		// 	// 	std::cout <<"nothing happens" << std::endl;
		// }
		//  break ; 
	}
	return (1);
}

/*Getters and Setters*/

/*Constructors*/
Engine::Engine(std::vector<Socket*> allSockets) : _allSockets(allSockets)
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

