#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <vector>
# include <fstream>
# include <string>

# include "../inc/webserv.hpp"
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
	std::string client_max_body_size_sd;
	std::string error_page_sd;

public:
	Location();
	~Location();
};

class Server
{
private:
	std::string listen;
	std::string server_name;
	std::string root;
	std::string index;
	std::string client_max_body_size;
	std::string error_page;

	std::vector<Location> locations;

public:
	void	addLocation(std::vector<Location> src);
	Socket	initListeningSocket();

	std::string getListen() const;
	std::string getServerName() const;

	Server();
	~Server(void);
};

std::ostream &operator<<(std::ostream &output_stream, Server &src);

#endif
