#include "./Server.hpp"


// ───── Server ────────────────────────────────────────────

Socket* Server::initListeningSocket()
{
	int	s_fd;
	
	std::cout << "	Creating socket" << std::endl;
	s_fd = socket(S_DOMAIN, SOCK_STREAM, 0);
	if (s_fd == -1)
		throw;
	ListeningSocket* listeningSocket = new ListeningSocket(s_fd);
	listeningSocket->setData(this->ip, this->port);
	listeningSocket->configureSocketOptions();
	listeningSocket->bindSocket();
	listeningSocket->listenConnectionSocket();
	//TODO : there is a list of errors returned in case of socket() fail, i may need to catch them as they all a macros 
	return (listeningSocket);
}

void	Server::addLocation(std::vector<Location> src)
{
	this->locations = src;
	return ;
}

std::string Server::getIp() const
{
	return (this->ip);
}

int Server::getPort() const
{
	return (this->port);
}

std::string Server::getAddr() const
{
	return (this->ip + ":" + std::to_string(this->port));
}

std::string Server::getServerName() const
{
	return (this->server_name);
}

Server::Server(std::string addr, int port) //constructor for mock servers
{
	this->ip = addr;
	this->port = port;
	this->server_name = "";
	this->root = "";
	this->index = "index.html";
	this->client_max_body_size = "1MB";
	this->error_page = "";

	std::vector<Location> locations;
}

Server::Server(const ServerParse& src) //constructor taking the ServerParse object
{
	std::cout << "Server constructor is called" << std::endl;
	
	std::string listen = src.get("listen").front(); 

	this->ip = listen.substr(0, listen.find(':'));
	this->port = std::stoi(listen.substr(listen.find(':') + 1));
	this->server_name = src.get("server_name").front();
	this->root = src.get("root").front();
	this->index = src.get("index").front();
	this->client_max_body_size = src.get("client_max_body_size").front();
	this->error_page = src.get("error_page").front();

	for (std::vector<LocationParse>::const_iterator it = src.getLocations().begin(); it != src.getLocations().end(); ++it)
	{
		Location loc(*it); // Create a Location object from the LocationParse object
		this->locations.push_back(loc);
	}
}

Server::~Server()
{
	std::cout << "Server destructor is called" << std::endl;
}

// ───── Location ──────────────────────────────────────────

Location::Location() //constructor for mock locations
{
	this->path_prefix = "-";
	this->root_sd = "server_default";
	this->index_sd = "server_default";
	this->autoindex = "off";
	this->limit_except = "GET POST DELETE HEAD";
	this->returns = "";
	this->cgi_pass = "off";
	this->upload_store = "forbidden";
	this->client_max_body_size_sd = "server_default";
	this->error_page_sd = "server_default";
}

Location::Location(const LocationParse& src) //constructor taking the LocationParse object
{
	this->path_prefix = src.get("path_prefix").front();
	this->root_sd = src.get("root").front();
	this->index_sd = src.get("index_sd").front();
	this->autoindex = src.get("autoindex").front();
	this->limit_except = src.get("limit_except").front();
	this->returns = src.get("return").front();
	this->cgi_pass = src.get("cgi_pass").front();
	this->upload_store = src.get("upload_store").front();
	this->client_max_body_size_sd = src.get("client_max_body_size_sd").front();
	this->error_page_sd = src.get("error_page_sd").front();
	this->proxy_pass = src.get("proxy_pass").front();
}

Location::~Location(){

}