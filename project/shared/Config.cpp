#include "Config.hpp"

/*Member functions*/

bool Config::startWebServ()
{
	int	listenSocket;

    std::cout << "	Starting Web Serv" << std::endl;
	for (std::vector<Port>::iterator it = this->_ports.begin(); it != this->_ports.end(); ++it)
	{ 
		try
		{
			listenSocket = it->createSocket();
			it->setListenSocket(listenSocket);
			it->optionsSocket();
			it->bindSocket();
			it->listenConnectionSocket();
			std::cout << *it << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cout << "Error creating/paring/listening socket for IP(" << it->getIp() <<\
				 "):PORT(" << it->getPort() << ") pair from vector" << std::endl;
			return (false);
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

// std::ostream& operator<<(std::ostream& output_stream, Config& src)
// {
// 	output_stream << "* Config Class info*" << std::endl;
// 	return output_stream;
// }

