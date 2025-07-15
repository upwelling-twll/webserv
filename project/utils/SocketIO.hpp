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
	//following statuses might be moved to other class
	ERROR_RESPONSE_RECEIVED,
};

enum ResponseStatus //will be  moved to httpResponse.hpp
{
	WAITING_START_LINE_RESPONSE,
	WAITING_HEADER_RESPONSE,
	WAITING_BODY_RESPONSE,
	READY_RESPONSE,
	ERROR_RESPONSE,
};

//HttpResponse class dummy
class HttpResponse
{
private:
	ResponseStatus	_status;
public:
	HttpResponse(): _status(WAITING_START_LINE_RESPONSE) {};
	~HttpResponse(){};

	ResponseStatus getStatus() const {
		return _status;
	}

	ResponseStatus insert(const std::string& rawMessage) {
		// Dummy implementation for the sake of example
		if (rawMessage.empty()) {
			_status = ERROR_RESPONSE;
			return _status;
		}
		_status = READY_RESPONSE;
		return _status;
	}
};


class SocketIO
{
private:
    // std::string			_buffer;
	SocketIOStatus		_status;
	std::string		 _rawMessage;


public:
	/*Member functions*/
	size_t	writeToClient(const std::string& message, int fd);
	int		readFromClient(int fd, AHttpRequest* _request);

	int		writeToDemon(const std::string& message, int fd);
	int		readFromDemon(int fd, HttpResponse* _response);

	/*Getters and Setters*/
	int		getStatus() const;

	/*Constructors*/
    SocketIO();


	/*Destructors*/
    ~SocketIO( void );
	
};

std::ostream& operator<<(std::ostream &output_stream, SocketIO& src);

#endif // SocketIO_HPP
