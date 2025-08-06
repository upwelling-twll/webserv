#ifndef SOCKETIO_HPP
# define SOCKETIO_HPP

# include <iostream>
# include "../inc/webserv.hpp"

class HttpResponse;

enum SocketIOStatus
{
	SENT_SOCKETIO,
	RECEIVED_SOCKETIO,
	ERROR_SOCKETIO,
	BUSY_SOCKETIO,
	IDLE_SOCKETIO,
	CLOSED_ERROR_SENDING_SOCKETIO,
	CLOSED_ERROR_RECEIVING_SOCKETIO,
	//following statuses are added for readFromClient use
	
	//TODO: following statuses might be moved to other class
	ERROR_RESPONSE_RECEIVED,

	//to compile grabage
	WAITING_FOR_DATA,
};


class SocketIO
{
private:
    // std::string			_buffer;
	SocketIOStatus		_status;
	std::string			_rawMessage;


public:
	/*Member functions*/
	size_t					writeToClient(const std::string& message, int fd);
	SocketIOStatus			readFromClient(int fd, AHttpRequest* _request);

	int		writeToDemon(const std::string& message, int fd);
	int		readFromDemon(int fd, HttpResponse* _response, std::string _rawMessage);


	/*Getters and Setters*/
	int		getStatus() const;

	/*Constructors*/
    SocketIO();


	/*Destructors*/
    ~SocketIO( void );
	
};

std::ostream& operator<<(std::ostream &output_stream, SocketIO& src);

#endif // SocketIO_HPP
