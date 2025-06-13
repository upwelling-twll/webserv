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

void	Engine::polloutSocketsHandle(std::vector<struct pollfd>& fds, size_t i, std::map<const Socket*, Connection*>& activeConnections)
{
	(void)fds; // to avoid unused parameter warning
	if (activeConnections[_allSockets[i]]->haveResponse())
	{
		_allConnections[i].sendToClients();
				// else
				// 	std::cout <<"nothing happens" << std::endl;
	}
}

void Engine::pollinSocketsHandle(std::vector<struct pollfd>& fds, size_t i, std::map<const Socket*, Connection*>& activeConnections)
{
	std::cout << "Have event on socket(fd=" << fds[i].fd << ")" << std::endl;
	std::cout << "Socket info: " << *_allSockets[i] << std::endl;
	std::cout << activeConnections[_allSockets[i]] << std::endl;
	if (_allSockets[i]->isListening())
	{
		std::cout << "New connection is being accepted" << std::endl;
		Connection* newConnection = new Connection(static_cast<ListeningSocket*>(_allSockets[i]));
		std::cout << "New connection created: " << *newConnection << std::endl;
		//add Client`s ConnectionSocket to _allSockets vector to use it as a key
		_allSockets.push_back(newConnection->getClientConnectionSocket());
		//add  new connection to activeConnections map to use its methods for recv and send
		activeConnections.insert(std::make_pair(_allSockets.back(), newConnection));
		//add new connection`s fd to _allConnections vector for poll()
		fds.push_back(newConnection->getPollFd());
		std::cout << "New connection created and added to active connections." << std::endl;
	}
	else
	{
		std::cout <<"receiveFromClient" << std::endl;
		activeConnections[_allSockets[i]]->handleInEvent();
	}
}

int Engine::engineRoutine(Config& config)
{
	(void)config;

	std::map<const Socket*, Connection*> activeConnections;
	std::vector<struct pollfd> fds;

	std::cout << "\n	*Engine routine has started*" << std::endl;
	int s = 0;
	for (std::vector<Socket*>::iterator it = _allSockets.begin(); it != _allSockets.end(); ++it)
	{
		fds.push_back(createPollFd((*it)->getFd(), POLLIN, 0));
		s++;
	}
	while(true)
	{
		int n = poll(fds.data(), fds.size(), 0); //timeout=0, then poll() will return without blocking.
		if (n < 0)
		{
			perror("poll");
			continue;
		}
		for (size_t i = 0; i < fds.size(); i++)
		{
			if (fds[i].revents & POLLIN)
				pollinSocketsHandle(fds, i, activeConnections);
			else if (fds[i].revents & POLLOUT)
				polloutSocketsHandle(fds, i, activeConnections);
		}
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

