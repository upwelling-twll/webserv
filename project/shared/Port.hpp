#ifndef PORT_HPP
# define PORT_HPP

# include <iostream>

class Port
{
private:
	const std::string		_ip;
	const unsigned int		_port;
public:
	/*Member functions*/
    // void method();

	/*Getters and Setters*/
	std::string const getIp();
	unsigned int getPort();

	/*Constructors*/
    Port(const std::string ip, const int port);
	Port(void);

	/*Destructors*/
    ~Port( void );

	/*Overload operators*/
	// Port &operator=(const Port& src);
};

std::ostream& operator<<(std::ostream &output_stream, Port& src);

#endif // PORT_HPP
