#include "../../shared/Server.hpp"
void Server::setListen(std::string newValue)
{
	this->listen = newValue;
}
void Server::setServerName(std::string newValue)
{
	this->server_name = newValue;
}
void Server::setRoot(std::string newValue)
{
	this->root = newValue;
}
void Server::setIndex(std::string newValue)
{
	this->index = newValue;
}
void Server::setClientMaxBodySize(std::string newValue)
{
	this->client_max_body_size = newValue;
}
void Server::setErrorPage(std::string newValue)
{
	this->error_page = newValue;
}