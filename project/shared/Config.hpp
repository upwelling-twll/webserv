#ifndef CONFIG_HPP
# define CONFIG_HPP

# include <iostream>
# include "Server.hpp"

class Config
{
private:
    std::vector<Server> servers;
	std::vector<Ports>	ports;

public:
	/*Member functions*/
    void method();

	/*Getters and Setters*/
	getServers();
	getConfigs();
	setServers(const Server server);
	setPorts(const Port port);

	/*Constructors*/
    Config(/*Parameterized Constructor*/);
	Config(void);

	/*Destructors*/
    ~Config( void );

	/*Overload operators*/
	Config &operator=(const Config& src);
};

std::ostream& operator<<(std::ostream &output_stream, Config& src);

#endif // CONFIG_HPP
