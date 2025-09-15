#include "./Server.hpp"

// ───── Location ──────────────────────────────────────────

bool Location::isMethodAllowed(const std::string& method) const
{
	if (limit_except.empty())
		return true; // default: allow everything
	else
		if (std::find(limit_except.begin(), limit_except.end(), method) != limit_except.end())
			return true;
	return false;
}

size_t Location::getMaxBodySize() const
{
	if (client_max_body_size_sd.empty())
		return SIZE_MAX;

    std::string s = client_max_body_size_sd;
    size_t multiplier = 1;

    if (s.size() > 2)
    {
        std::string suffix = s.substr(s.size() - 2);
        if (suffix == "KB") 
		{ 
			multiplier = 1024; 
			s = s.substr(0, s.size() - 2); 
		}
        else if (suffix == "MB") 
		{ 
			multiplier = 1024 * 1024; 
			s = s.substr(0, s.size() - 2); 
		}
        else if (suffix == "GB") 
		{ 
			multiplier = 1024ull * 1024ull * 1024ull; 
			s = s.substr(0, s.size() - 2); 
		}
    }
    return std::stoul(s) * multiplier;
}

std::string Location::getRoot_sd() const
{
	return (this->root_sd);
}

std::string Location::getUpload_store() const
{
	return (this->upload_store);
}

Location::Location() //constructor for mock locations
{
	this->path_prefix = "-";
	this->root_sd = "server_default";
	this->index_sd = "server_default";
	this->autoindex = "off";
	this->limit_except.clear();
	this->limit_except.push_back("GET");
	this->returns = "";
	this->cgi_pass = "off";
	this->upload_store = "forbidden";
	this->client_max_body_size_sd = "1024";
	this->error_page_sd = "server_default";
}

Location::Location(const LocationParse& src) //constructor taking the LocationParse object
{
	this->path_prefix = src.get("path_prefix").front();
	this->root_sd = src.get("root").front();
	this->index_sd = src.get("index_sd").front();
	this->autoindex = src.get("autoindex").front();
	this->limit_except = src.get("limit_except");
	if ((this->limit_except).front() == "GET POST DELETE HEAD")
	{
		this->limit_except.clear();
		this->limit_except.push_back("GET");
		this->limit_except.push_back("POST");
		this->limit_except.push_back("DELETE");
		this->limit_except.push_back("HEAD");
	}
	this->returns = src.get("return").front();
	this->cgi_pass = src.get("cgi_pass").front();
	this->upload_store = src.get("upload_store").front();
	this->client_max_body_size_sd = src.get("client_max_body_size_sd").front();
	this->error_page_sd = src.get("error_page_sd").front();
	this->proxy_pass = src.get("proxy_pass").front();
}

Location::~Location(){
}

std::string Location::getPathPrefix() const
{
	return (this->path_prefix);
}


// ───── Server ────────────────────────────────────────────

const Location* Server::matchLocation(const std::string& uri) const
{
    for (std::vector<Location>::const_iterator it = locations.begin(); it != locations.end(); ++it)
	{
		if (uri.find(it->getPathPrefix()) == 0) 
		{
            return &(*it);
        }
    }
    return NULL;
}

const Location* Server::matchUploadLocation(const std::string& uri) const
{
    for (std::vector<Location>::const_iterator it = locations.begin(); it != locations.end(); ++it)
	{
		std::string uriUploadStore = it->getRoot_sd() + uri;
		std::cout << "DEBUG: searching uriUploadStore = " << uriUploadStore << std::endl;
		std::cout << "DEBUG: comparing with location upload_store = " << it->getUpload_store() << std::endl;
		if (uriUploadStore == it->getUpload_store()) 
		{
            return &(*it);
        }
    }
    return NULL;
}

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
