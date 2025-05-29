#ifndef CONNECTION_HPP
# define CONNECTION_HPP

# include <iostream>

class httpRequest;

class Connection
{
private:
    httpRequest _request;
	bool		_stayAlive;

public:
	/*Member functions*/
    bool	connectSocket();
	bool	disconnectSocket();

	/*Getters and Setters*/

	/*Constructors*/
    Connection(/*Parameterized Constructor*/);
	Connection(void);

	/*Destructors*/
    ~Connection( void );

	/*Overload operators*/
	Connection &operator=(const Connection& src);
};

std::ostream& operator<<(std::ostream &output_stream, Connection& src);

#endif // CONNECTION_HPP
