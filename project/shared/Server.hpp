#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <vector>
# include <fstream>
# include <string>

# include "../inc/webserv.hpp"

class Socket;
class Port;

class ServerParse; //needed for constructor
class LocationParse; //needed for constructor
class Location
{
private:
	std::string path_prefix;
	std::string root_sd;
	std::string index_sd;
	std::string autoindex;
	std::string limit_except;
	std::string returns;
	std::string cgi_pass;
	std::string upload_store;
	std::string client_max_body_size_sd; //convert to bytes size_t
	std::string error_page_sd;
	std::string proxy_pass; //might be converted to str ip and int port

public:
	bool isMethodAllowed(const std::string& method) const;

	std::string getPathPrefix() const;
	size_t getMaxBodySize() const; //in bytes
	std::string getRoot_sd() const;

	Location(); //constructor for mock locations
	Location(const LocationParse& src); //constructor taking the LocationParse object
	~Location();
};

class Server
{
private:
	std::string ip;
	int 		port;
	std::string server_name;
	std::string root;
	std::string index;
	std::string client_max_body_size;
	std::string error_page;

	std::vector<Location> locations;

public:
	void		addLocation(std::vector<Location> src); //not used can delete
	Socket*		initListeningSocket();
	const Location* matchLocation(const std::string& uri) const;

	std::string getIp() const;
	int			getPort() const;
	std::string getAddr() const;
	std::string getServerName() const;

	Server(std::string addr, int port); //constructor for mock servers
	Server(const ServerParse& src); //constructor taking the ServerParse object
	~Server(void);
};

std::ostream &operator<<(std::ostream &output_stream, Server &src);

#endif