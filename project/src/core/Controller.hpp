#ifndef CONTROLLER_HPP
# define CONTROLLER_HPP

# include <iostream>

enum ControllerStatus
{
	SENT,
	RECEIVED,
	ERROR,
	BUSY,
	IDLE,
	CLIENT_CLOSED_ERROR_SENDING_DATA_CONTROLLER,

};

class Controller
{
private:
    std::string			_buffer;
	ControllerStatus	_status;

public:
	/*Member functions*/
	int		writeToClient(const std::string& message, int fd);
	int		readFromClient(int fd);

	int		writeToDemon(const std::string& message, int fd);
	int		readFromDemon(int fd);

	/*Getters and Setters*/
	int		getStatus() const;

	/*Constructors*/
    Controller();


	/*Destructors*/
    ~Controller( void );
	
};

std::ostream& operator<<(std::ostream &output_stream, Controller& src);

#endif // CONTROLLER_HPP
