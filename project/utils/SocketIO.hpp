#ifndef SOCKETIO_HPP
# define SOCKETIO_HPP

# include <iostream>
# include "../inc/webserv.hpp"

enum SocketIOStatus
{
	SENT_SOCKETIO,
	RECEIVED_SOCKETIO,
	ERROR_SOCKETIO,
	BUSY_SOCKETIO,
	IDLE_SOCKETIO,
	CLOSED_ERROR_SENDING_SOCKETIO,
	CLOSED_ERROR_RECEIVING_SOCKETIO,
};

class AHttpRequest; // Forward declaration of AHttpRequest class
class SocketIO
{
private:
    // std::string			_buffer;
	SocketIOStatus		_status;


public:
	/*Member functions*/
	size_t	writeToClient(const std::string& message, int fd);
	int		readFromClient(int fd, AHttpRequest* _request, std::string _rawMessage);

	int		writeToDemon(const std::string& message, int fd);
	int		readFromDemon(int fd, std::string _messageReseived);

	/*Getters and Setters*/
	int		getStatus() const;

	/*Constructors*/
    SocketIO();


	/*Destructors*/
    ~SocketIO( void );
	
};

std::ostream& operator<<(std::ostream &output_stream, SocketIO& src);

#endif // SocketIO_HPP
