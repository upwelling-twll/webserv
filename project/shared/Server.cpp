#include "Server.hpp"

const char *Location::properties[Location::K] = {
	"path_prefix", "root", "index_sd", "autoindex", "limit_except",
	"return", "cgi_pass", "upload_store", "client_max_body_size_sd", "error_page_sd"};

const char *Server::properties[Server::K] = {
	"listen", "server_name", "root", "index", "client_max_body_size", "error_page"};

Location::Location()
{
	const char *d[Location::K] = {
		"-", "server_default", "server_default", "off", "GET POST DELETE HEAD",
		"", "off", "forbidden", "server_default", "server_default"};
	for (std::size_t i = 0; i < K; ++i)
		values[i].push_back(d[i]);
}

bool Location::hasProperty(const std::string &k) const
{
	for (std::size_t i = 0; i < K; ++i)
		if (k == properties[i])
			return true;
	return false;
}

std::string Location::get(const std::string &k) const
{
	for (std::size_t i = 0; i < K; ++i)
		if (k == properties[i] && !values[i].empty())
			return values[i].back();
	return "";
}

void Location::set(const std::string &k, const std::string &v)
{
	for (std::size_t i = 0; i < K; ++i)
		if (k == properties[i])
		{
			values[i].push_back(v);
			return;
		}
}

std::string Location::getProperties() const
{
	std::ostringstream o;
	for (std::size_t i = 0; i < K; ++i)
	{
		if (i)
			o << ' ';
		o << properties[i];
	}
	return o.str();
}

void Location::print(int indent) const
{
	std::string pad(indent * 2, ' ');
	std::cout << pad << "location {\n";
	for (std::size_t i = 0; i < K; ++i)
	{
		bool ch = values[i].size() > 1;
		std::cout << pad << "  " << properties[i] << ": "
				  << (ch ? "\033[32m" : "\033[33m")
				  << (values[i].empty() ? "<unset>" : values[i].back())
				  << "\033[0m\n";
	}
	std::cout << pad << "}\n";
}

Server::Server()
{
	const char *d[Server::K] = {"80", "", "", "index.html", "1MB", ""};
	for (std::size_t i = 0; i < K; ++i)
		values[i].push_back(d[i]);
}

bool Server::hasProperty(const std::string &k) const
{
	for (std::size_t i = 0; i < K; ++i)
		if (k == properties[i])
			return true;
	return false;
}

std::string Server::get(const std::string &k) const
{
	for (std::size_t i = 0; i < K; ++i)
		if (k == properties[i] && !values[i].empty())
			return values[i].back();
	return "";
}

void Server::set(const std::string &k, const std::string &v)
{
	for (std::size_t i = 0; i < K; ++i)
		if (k == properties[i])
		{
			values[i].push_back(v);
			return;
		}
}

void Server::addLocation(const Location &loc) { locations.push_back(loc); }
const std::vector<Location> &Server::getLocations() const { return locations; }

std::string Server::getProperties() const
{
	std::ostringstream o;
	for (std::size_t i = 0; i < K; ++i)
	{
		if (i)
			o << ' ';
		o << properties[i];
	}
	return o.str();
}

void Server::print() const
{
	std::cout << "server {\n";
	for (std::size_t i = 0; i < K; ++i)
	{
		bool ch = values[i].size() > 1;
		std::cout << "  " << properties[i] << ": "
				  << (ch ? "\033[32m" : "\033[33m")
				  << (values[i].empty() ? "<unset>" : values[i].back())
				  << "\033[0m\n";
	}
	for (std::size_t j = 0; j < locations.size(); ++j)
		locations[j].print(2);
	std::cout << "}\n";
}