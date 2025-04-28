#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <vector>

struct ServerStructLocation
{

	std::string path_prefix = "-";
	std::string root_sd = "server_default";
	std::string index_sd = "server_default";
	std::string autoindex = "off";
	std::string limit_except = "GET POST DELETE HEAD";
	std::string returns = "";
	std::string cgi_pass = "off";
	std::string upload_store = "forbidden"; 
	std::string client_max_body_size_sd = "server_default";
	std::string error_page_sd = "server_default";
};
struct ServerStruct
{
	std::string listen = "80";
	std::string server_name = "";
	std::string root = "";
	std::string index = "index.html";
	std::string client_max_blody_size = "1MB";
	std::string error_page = "";
	ServerStructLocation location;
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

	std::vector<ServerStructLocation> locations;

public:
	Server(ServerStruct server_struct);
	Server();
	~Server(void);

	Server &operator=(const Server &src);
};

std::ostream &operator<<(std::ostream &output_stream, Server &src);

#endif
