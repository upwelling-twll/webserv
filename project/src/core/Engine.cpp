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

void	Engine::polloutSocketsHandle(size_t i, std::map<const Socket*, Connection*>& activeConnections)
{
	(void)_fds; // to avoid unused parameter warning
	std::map<const Socket*, Connection*>::iterator it = activeConnections.find(_allSockets[i]);
	ConnectionStatus status = it->second->getStatus();

	if (status == PREPARED_RESPONSE)
	{
		std::cout << "Connection has response, sending it to client" << std::endl;
		_controller->send(it->second);
		it->second->processConnectionStatusSending(); //might not need
	}
	else if (status == PROCESSING_RESPONSE)
		std::cout << "Connection is processing response, nothing to send" << std::endl;
	else
	{
		std::cout << "Connection has no response" << std::endl;
	}
}

void Engine::pollinSocketsHandle(size_t i, std::map<const Socket*, Connection*>& activeConnections)
{
	std::cout << "pollinSocketsHandle: Have event on socket(fd=" << _fds[i].fd << ")" << std::endl;
	printActiveConnections(activeConnections);
	std::cout << "pollinSocketsHandle: Socket info: " << *_allSockets[i] << std::endl;
	if (_allSockets[i]->isListening())
	{
		std::cout << "pollinSocketsHandle: New connection is being accepted" << std::endl;
		Connection* newConnection = new Connection(static_cast<ListeningSocket*>(_allSockets[i]), _config);
		std::cout << "pollinSocketsHandle: New connection created: " << *newConnection << std::endl;
		//add Client`s ConnectionSocket to _allSockets vector to use it as a key
		_allSockets.push_back(newConnection->getClientConnectionSocket());
		//add  new connection to activeConnections map to use its methods for recv and send
		activeConnections.insert(std::make_pair(_allSockets.back(), newConnection));
		//add new connection`s fd to _allConnections vector for poll()
		_fds.push_back(newConnection->getPollFd());
		std::cout << "pollinSocketsHandle: New connection created and added to active connections." << std::endl;
	}
	else
	{
		std::map<const Socket*, Connection*>::iterator it = activeConnections.find(_allSockets[i]);
		if (it != activeConnections.end())
		{
			std::cout <<"pollinSocketsHandle: receive in socket" << std::endl;
			_controller->receive(it->second);
		}	
	}
}

void print_pfds(const std::vector<struct pollfd>& pfds)
{
	std::cout << "Current pollfds:" << std::endl;
	for (size_t i = 0; i < pfds.size(); i++)
	{
		std::cout << "fd: " << pfds[i].fd
				  << ", events: " << pfds[i].events
				  << ", revents: " << pfds[i].revents << std::endl;
	}
	std::cout << "Total pollfds: " << pfds.size() << std::endl;
	std::cout << "------------------------" << std::endl;
}

void Engine::updateAliveConnections(std::map<const Socket*, Connection*>& activeConnections, std::vector<struct pollfd>& pfds)
{
		//std::cout << "Updating alive connections..." << std::endl;
		for (std::map<const Socket*, Connection*>::iterator it = activeConnections.begin(); it != activeConnections.end(); )
		{
			//std::cout << "Checking connection for socket fd=" << it->first->getFd() << std::endl;
			if (it->first->isListening() == false &&  it->second && (it->second->getStatus() == SENT_TO_CLIENT \
				|| it->second->getStatus() == ERROR_RECEIVING_DATA_CLOSE_CONNECTION \
				|| it->second->getStatus() == CLIENT_CLOSED_ERROR_RECEIVING_DATA \
				) && it->second->isActive() == false)
			{	
				// Remove the corresponding pollfd from _fds
				std::cout << "Someone will be erased from here!" << std::endl;
				int fd = it->first->getFd();
				for (size_t j = 0; j < pfds.size(); ++j)
				{
					if (pfds[j].fd == fd)
					{
						if (fd >= 0) // Ensure the file descriptor is valid
						{
							close(fd); // Close the socket file descriptor
							std::cout << "Closed socket with fd=" << fd << std::endl;
						}
						pfds.erase(pfds.begin() + j);
						std::cout << "Removed pollfd with fd=" << fd << " from pollfds." << std::endl;
						break;
					}
				}
				for (std::vector<Socket*>::iterator it = _allSockets.begin(); it != _allSockets.end();)
				{
					if ((*it)->getFd() == fd)
					{
						std::cout << "Removing socket with fd=" << fd << " from _allSockets." << std::endl;
						it = _allSockets.erase(it);
					}
					else
						++it;
				}
				it->second->clean();
				delete it->second; // Delete the Connection object
				it = activeConnections.erase(it);
			}
			else
				++it;
		}
		//std::cout << "Alive connections updated." << std::endl;
	}

int Engine::engineRoutine(Config& config)
{
	_config = config;

	std::map<const Socket*, Connection*> activeConnections;

	std::cout << "\n	*Engine routine has started*" << std::endl;
	for (std::vector<Socket*>::iterator it = _allSockets.begin(); it != _allSockets.end(); ++it)
	{
		_fds.push_back(createPollFd((*it)->getFd(), POLLIN | POLLOUT, 0));
	}
	
	int dbg = 0;
	while(true)
	{
		dbg++;
		if (dbg % 100000000 == 0)
			print_pfds(_fds);
		int n = poll(_fds.data(), _fds.size(), 0); //timeout=0, then poll() will return without blocking.
		if (n < 0)
		{
			perror("poll");
			continue;
		}
		// std::cout << "poll returned with n=" << n << std::endl;
		for (size_t i = 0; i < _fds.size(); i++)
		{
			// std::cout << "Checking _fds[" << i << "] with fd=" << _fds[i].fd << std::endl;
			if (_fds[i].revents & POLLIN)
			{
				std::cout << "WILL POLLIN event on socket fd=" << _fds[i].fd << std::endl;
				pollinSocketsHandle(i, activeConnections);
				// break;
				std::cout << "completed pollin socket handle" << std::endl;
				printActiveConnections(activeConnections);
			}
			else if ((_fds[i].revents & POLLOUT))
			{
				// std::cout << "Checking POLLOUT event on socket fd=" << _fds[i].fd << std::endl;
				std::map<const Socket*, Connection*>::iterator it = activeConnections.find(_allSockets[i]);
				if (it != activeConnections.end() && it->second->getStatus() == PREPARED_RESPONSE)
				{
					std::cout << "WILL POLLOUT event on socket fd=" << _fds[i].fd << std::endl;
					polloutSocketsHandle(i, activeConnections);
					break;
				}
			}
		}
		// std::cout << "will check updateAliveConnection" << std::endl;
		updateAliveConnections(activeConnections, _fds);
	}
	return (1);
}

/*Getters and Setters*/

/*Constructors*/
Engine::Engine(std::vector<Socket*> allSockets, Config& config) : _allSockets(allSockets), _config(config)
{
   std::cout << "Engine parameterized constructor is called" << std::endl;
//    Controller controller;
//    _controller = controller;
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

