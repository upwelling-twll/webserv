#include "Config.hpp"

/*Member functions*/

void Config::addSocketToVector(Socket *s)
{
	std::cout << "adding socket to vector:" << s->getFd() << std::endl;
	this->_allSockets.push_back(s);
}

bool Config::startWebServ()
{
    std::cout << "	Starting Web Serv" << std::endl;
	{
		for (std::vector<Server>::iterator it = this->_servers.begin(); it != this->_servers.end(); ++it)
		{
			try
			{
				addSocketToVector(it->initListeningSocket());
			}
			catch(const std::exception& e)
			{
				std::cout << "Error adding socket to vector:" << it->getAddr() << std::endl;
				std::cerr << e.what() << '\n';
			}
		}
	}
	return (true);
}

void	Config::closeAllFds()
{
	for(std::vector<Port>::iterator it = this->_ports.begin(); it != this->_ports.end(); ++it)
	{
		it->closeFd();
	}
}

/*Getters and Setters*/
std::vector<Server>	const Config::getServers()
{
	return (this->_servers);
}

std::vector<Port> Config::getPorts()
{
	return (this->_ports);
}

std::vector<Socket*> Config::getAllSockets() const
{
	return (this->_allSockets);
}

/*Constructors*/
Config::Config(std::vector<Server> servers) :  _servers(servers)
{
	for (std::vector<Server>::iterator it = servers.begin(); it != servers.end(); ++it)
	{
		Port port(it->getIp(), it->getPort());
		_ports.push_back(port);
	}
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

// std::ostream& operator<<(std::ostream& output_stream, Config& src)
// {
// 	output_stream << "* Config Class info*" << std::endl;
// 	return output_stream;
// }

