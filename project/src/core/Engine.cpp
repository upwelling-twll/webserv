#include "Engine.hpp"

/*Member functions*/
int Engine::engineRoutine(Config config)
{
	std::vector<Socket> fdsPool = this->_allSockets;
	fd_set *masterFds;
	
	std::cout << "	Engine routine is called" << std::endl;
	FD_ZERO(masterFds);
	for (std::vector<Socket>::iterator it = fdsPool.begin(); it != fdsPool.end(); ++it)
	{
		FD_SET(it->getFd(), masterFds);
	}
	int maxFd = fdsPool.back().getFd();
	while(1)
	{
		receiveFromClients(fdsPool);
		sendToClients(fdsPool);
		acceptNewClients(fdsPool);
	}
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

