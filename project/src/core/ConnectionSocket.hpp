#ifndef CONNECTIONSOCKET_HPP
# define CONNECTIONSOCKET_HPP

# include <iostream>

class ConnectionSocket : public Socket
{
private:
    

public:
	/*Member functions*/
    void method();

	/*Getters and Setters*/

	/*Constructors*/
    ConnectionSocket(/*Parameterized Constructor*/);
	ConnectionSocket(void);

	/*Destructors*/
    ~ConnectionSocket( void );

	/*Overload operators*/
	ConnectionSocket &operator=(const ConnectionSocket& src);
};

std::ostream& operator<<(std::ostream &output_stream, ConnectionSocket& src);

#endif // CONNECTIONSOCKET_HPP
