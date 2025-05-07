#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

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
	void setPathPrefix(std::string newValue);
	void setRootSd(std::string newValue);
	void setIndexSd(std::string newValue);
	void setAutoIndex(std::string newValue);
	void setLimitExcept(std::string newValue);
	void setReturns(std::string newValue);
	void setCgiPass(std::string newValue);
	void setUploadStore(std::string newValue);
	void setClientMaxBodySizeSd(std::string newValue);
	void setErrorPageSd(std::string newValue);
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
	Server();
	~Server(void);
	void setListen(std::string newValue);
	void setServerName(std::string newValue);
	void setRoot(std::string newValue);
	void setIndex(std::string newValue);
	void setClientMaxBodySize(std::string newValue);
	void setErrorPage(std::string newValue);
};

std::ostream &operator<<(std::ostream &output_stream, Server &src);

#endif
