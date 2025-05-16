#include "./Server.hpp"

Socket Server::initListeningSocket()
{
	
}

void	Server::addLocation(std::vector<Location> src)
{
	this->locations = src;
	return ;
}

std::string Server::getListen() const
{
	return (this->listen);
}

std::string Server::getServerName() const
{
	return (this->server_name);
}

Server::Server()
{
	this->listen = "80";
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