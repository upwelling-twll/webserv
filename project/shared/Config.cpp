#include "Config.hpp"

/*Member functions*/
// void Config::method()
// {
//     // Method implementation
// }

/*Getters and Setters*/
std::vector<Server>	const Config::getServers()
{
	return (this->_servers);
}

std::vector<Port>	const Config::getPorts()
{
	return (this->_ports);
}

/*Constructors*/
Config::Config(std::vector<Server> servers, std::vector<Port> ports) : \
	 _servers(servers), _ports(ports)
{
   std::cout << "Config parameterized constructor is called" << std::endl;
}

Config::Config()
{
    std::cout << "Config default constructor is called" << std::endl;
}

/*Destructors*/
Config::~Config( void )
{
    std::cout << "Config destructor is called" << std::endl;
}

/*Overload operators*/
Config& Config::operator=(const Config& src)
{
	std::cout << "Config copy assignment is called" << std::endl;
	if (this != &src)
	{
		// Assinment variables
	}
	return (*this);
}

std::ostream& operator<<(std::ostream& output_stream, Config& src)
{
	output_stream << "* Config Class info*" << std::endl;
	return output_stream;
}

