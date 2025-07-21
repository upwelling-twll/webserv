#ifndef CONNECTION_HPP
# define CONNECTION_HPP

# include <iostream>
# include <ctime>

# include "../../inc/webserv.hpp"

class AHttpRequest;
class ListeningSocket;
class ConnectionSocket;
class HttpStream;

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
	std::string		_responseMessage;

public:
	HttpResponse(): _status(WAITING_START_LINE_RESPONSE) {};
	~HttpResponse(){};

	ResponseStatus getStatus() const {
		return _status;
	}
	
	std::string getResponseMessage() const {
		return _responseMessage;
	}

	ResponseStatus insert(const std::string& rawMessage) {
		// Dummy implementation for the sake of example
		if (rawMessage.empty()) {
			_status = ERROR_RESPONSE;
			return _status;
		}
		_status = READY_RESPONSE;
		_responseMessage = rawMessage;
		return _status;
	}
};

enum ConnectionStatus
{
	IDLE, 						//0
	RECEIVING_REQUEST,			//1
	PROCESSING_RESPONSE,		//2
	// HAS_REQUEST,
	// WAITING_FOR_RESPONSE,
	// HAS_RESPONSE,
	READY_FOR_FORMATTING_RESPONSE,	//3			 	 //used in handleInEvent
	ERROR_REQUEST_RECEIVED,			//4			 	 //used in handleInEvent
	WAITING_FOR_DATA,				//5			 	 //used in handleInEvent
	CLENT_CLOSED_READY_FOR_FORMATTING_RESPONSE, //6	 //used in handleInEvent
	CLIENT_CLOSED_ERROR_RECEIVING_DATA, 		//7	 //used in handleInEvent
	ERROR_RECEIVING_DATA_CLOSE_CONNECTION,		//8	 //used in handleInEvent
	// CLOSED,
	PREPARED_RESPONSE,				//9 			 //used in handleOutEvent
	SENT_TO_CLIENT,					//10			 //used in handleOutEvent
	ERROR_CONNECTION,				//11
	CLIENT_CLOSED_ERROR_SENDING_DATA_CONNECTION,	//12
};

class Connection
{
private:
	/*Private members*/
	std::string					_rawMessage;
	std::string					_buffer;
	ConnectionStatus			_status;
	time_t						_timeLastUsed;
	size_t						_bytesSent;

	ListeningSocket*			_serverListeningSocket;
	ConnectionSocket*			_clientConnectionSocket;

	AHttpRequest*				_request;
	HttpResponse*				_response;
	bool						_active; //may remove as it is not used

	struct pollfd				_pollFd;

public:
	/*Member functions*/
	void			receiveMessage();
	void			processConnectionStatusReceiving();
	void			processConnectionStatusSending();
	bool			haveResponse();
	bool			sendToClient();
	struct pollfd	createConnectionSocket(ListeningSocket* serverListeningSocket);
	void			changeSocketMode(short mode, pollfd& pollFd);
	// bool	disconnectSocket();

	/*Getters and Setters*/
	bool			isActive();
	struct pollfd	getPollFd() const;

	/*Getters for private members*/
	std::string					getRawMessage() const;
	std::string					getBuffer() const;
	ConnectionStatus			getStatus() const;
	time_t						getTimeLastUsed() const;
	ListeningSocket*			getServerListeningSocket() const;
	ConnectionSocket*			getClientConnectionSocket() const;
	AHttpRequest*				getRequest() const;
	HttpResponse*				getResponse() const;

	/*Constructors*/
    Connection(ListeningSocket* serverListeningSocket);

	/*Destructors*/
    ~Connection( void );

	/*Overload operators*/
	Connection &operator=(const Connection& src);
};

std::ostream& operator<<(std::ostream &output_stream, Connection& src);

#endif // CONNECTION_HPP
