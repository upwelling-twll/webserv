#include "./Server.hpp"

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

std::string Server::getAddr() const
{
	return (this->ip ); //+ ":" + std::to_string(this->port)
}

std::string Server::getServerName() const
{
	return (this->server_name);
}

Server::Server(std::string addr, int port)
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

Server::~Server()
{
	std::cout << "Server destructor is called" << std::endl;
}

Location::Location() {
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

Location::~Location(){

}