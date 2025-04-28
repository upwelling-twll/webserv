#include "Config.hpp"

/*Member functions*/
void Config::method()
{
    // Method implementation
}

/*Getters and Setters*/
std::vector	const Config::getServers()
{

}

std::vector	const Config::getPorts()
{
	
}

void const	Config::setServers()
{
	
}

void const	Config::setPorts()
{
	
}


/*Constructors*/
Config::Config(/*Parameterized Constructor*/)
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

