#ifndef CONTROLLER_HPP
# define CONTROLLER_HPP

# include <iostream>
# include "../../inc/webserv.hpp"

class Connection;

class Controller
{
private:
    // Add member variables here

public:
	/*Member functions*/
	void	receive(Connection* connection);
	void	send(Connection* connection);
	/*Getters and Setters*/

	/*Constructors*/
    // Controller(/*Parameterized Constructor*/);
	Controller(void);

	/*Destructors*/
    ~Controller( void );

	/*Overload operators*/
	// Controller &operator=(const Controller& src);
};

// std::ostream& operator<<(std::ostream &output_stream, Controller& src);

#endif // CONTROLLER_HPP
