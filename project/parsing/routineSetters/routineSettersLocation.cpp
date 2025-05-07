#include "../../shared/Server.hpp"
void Location::setPathPrefix(std::string newValue)
{
	this->path_prefix = newValue;
	
}
void Location::setRootSd(std::string newValue)
{
	this->root_sd = newValue;
	
}
void Location::setIndexSd(std::string newValue)
{
	this->index_sd = newValue;
	
}
void Location::setAutoIndex(std::string newValue)
{
	this->autoindex = newValue;
	
}
void Location::setLimitExcept(std::string newValue)
{
	this->limit_except = newValue;
}
void Location::setReturns(std::string newValue)
{
	this->returns = newValue;
}
void Location::setCgiPass(std::string newValue)
{
	this->cgi_pass = newValue;
}
void Location::setUploadStore(std::string newValue)
{
	this->upload_store = newValue;
}
void Location::setClientMaxBodySizeSd(std::string newValue)
{
	this->client_max_body_size_sd = newValue;
}
void Location::setErrorPageSd(std::string newValue)
{
	this->error_page_sd = newValue;
}