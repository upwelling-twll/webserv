#ifndef CONFIG_HPP
# define CONFIG_HPP

# include <iostream>
# include "Server.hpp"
# include "Port.hpp"
class Config
{
private:
    std::vector<Server> _servers;
	std::vector<Port>	_ports;

public:
	/*Member functions*/
    // void method();

	/*Getters and Setters*/
	std::vector<Server>	const getServers();
	std::vector<Port>	const getPorts();

	/*Constructors*/
    Config(std::vector<Server> servers, std::vector<Port> ports);
	Config(void);

	/*Destructors*/
    ~Config( void );

	/*Overload operators*/
	Config &operator=(const Config& src);
};

std::ostream& operator<<(std::ostream &output_stream, Config& src);

#endif // CONFIG_HPP
