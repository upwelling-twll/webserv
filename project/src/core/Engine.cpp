#include "Engine.hpp"

/*Member functions*/
int Engine::engineRoutine(Config config)
{
	(void)config;
	std::cout << "	Engine routine is called" << std::endl;
	for (std::vector<Socket>::iterator it = this->_allSockets.begin(); it != this->_allSockets.end(); ++it)
	{
		std::cout << "Engine routine is called" << std::endl;
		it->handler(*it);
	}
	return (1);
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

