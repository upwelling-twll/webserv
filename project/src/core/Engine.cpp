#include "Engine.hpp"

/*Member functions*/

struct pollfd Engine::createPollFd(int fd, short events, short revents)
{
	struct pollfd newPollFd;
	
	newPollFd.fd = fd;
	newPollFd.events = events;
	newPollFd.revents = revents;

	return (newPollFd);
}

bool	Engine::haveResponse(struct pollfd fd)
{
	// std::cout << "	Need to check my response" << std::endl;
	if (fd.fd)
		return (true);
	return (false);
}

bool	Engine::sendToClients()
{
	//TODO move this methos to Connection class
	// std::cout << "	Giving my response to the client" << std::endl;
	return (false);
}

void	Engine::pollinSocketsHandle(std::vector<struct pollfd>& fds, std::map<const Socket*, Connection*>& activeConnections)
{
	(void)activeConnections; // Suppress unused variable warning
	for (size_t i = 0; i < fds.size(); i++)
		{
			if (haveResponse(fds[i]))
			{
				sendToClients();
				// else
				// 	std::cout <<"nothing happens" << std::endl;
			}
			//  break ; 
		}
}

void Engine::polloutSocketsHandle(std::vector<struct pollfd>& fds, std::map<const Socket*, Connection*>& activeConnections)
{
	for (size_t i = 0; i < fds.size(); i++)
		{
			if (fds[i].revents & POLLIN)
			{
				std::cout << "Have event on socket(fd=" << fds[i].fd << ")" << std::endl; 
				if (_allSockets[i]->isListening())
				{
					Connection* newConnection = new Connection(static_cast<ListeningSocket*>(_allSockets[i]));			
					activeConnections.insert(std::make_pair(_allSockets[i], newConnection));
					fds.push_back(newConnection->getPollFd());
				}
				else
				{
					std::cout <<"receiveFromClients" << std::endl;
					_allSockets[i]->handle();
				}
			}
		}
}

int Engine::engineRoutine(Config& config)
{
	(void)config;

	// Removed unused variable to avoid errors
	std::map<const Socket*, Connection*> activeConnections;
	std::vector<struct pollfd> fds;

	std::cout << "	Engine routine is called" << std::endl;
	int s = 0;
	for (std::vector<Socket*>::iterator it = _allSockets.begin(); it != _allSockets.end(); ++it)
	{
		fds.push_back(createPollFd((*it)->getFd(), POLLIN, 0));
		s++;
	}
	std::cout << "	s= " << s << std::endl;
	// int maxFd = _allSockets.back().getFd();
	while(true)
	{
		int n = poll(fds.data(), fds.size(), 0); //timeout=0, then poll() will return without blocking.
		if (n < 0)
		{
			perror("poll");
			continue;
		}
		polloutSocketsHandle(fds, activeConnections);
		pollinSocketsHandle(fds, activeConnections);
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

