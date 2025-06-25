#include "./ServerParse.hpp"

LocationParse::LocationParse() {
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

LocationParse::~LocationParse(){

const char *LocationParse::properties[LocationParse::K] = {
	"path_prefix", "root", "index_sd", "autoindex", "limit_except",
	"return", "cgi_pass", "upload_store", "client_max_body_size_sd", "error_page_sd"};

const char *ServerParse::properties[ServerParse::K] = {
	"listen", "server_name", "root", "index", "client_max_body_size", "error_page"};

LocationParse::LocationParse()
{
	const char *d[LocationParse::K] = {
		"-", "server_default", "server_default", "off", "GET POST DELETE HEAD",
		"", "off", "forbidden", "server_default", "server_default"};
	for (std::size_t i = 0; i < K; ++i)
		values[i].push_back(d[i]);
}

bool LocationParse::hasProperty(const std::string &k) const
{
	for (std::size_t i = 0; i < K; ++i)
		if (k == properties[i])
			return true;
	return false;
}

std::string LocationParse::get(const std::string &k) const
{
	for (std::size_t i = 0; i < K; ++i)
		if (k == properties[i] && !values[i].empty())
			return values[i].back();
	return "";
}

void LocationParse::set(const std::string &k, const std::string &v)
{
	for (std::size_t i = 0; i < K; ++i)
		if (k == properties[i])
		{
			values[i].push_back(v);
			return;
		}
}

std::string LocationParse::getProperties() const
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

void LocationParse::print(int indent) const
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

ServerParse::ServerParse()
{
	const char *d[ServerParse::K] = {"80", "", "", "index.html", "1MB", ""};
	for (std::size_t i = 0; i < K; ++i)
		values[i].push_back(d[i]);
}

bool ServerParse::hasProperty(const std::string &k) const
{
	for (std::size_t i = 0; i < K; ++i)
		if (k == properties[i])
			return true;
	return false;
}

std::string ServerParse::get(const std::string &k) const
{
	for (std::size_t i = 0; i < K; ++i)
		if (k == properties[i] && !values[i].empty())
			return values[i].back();
	return "";
}

void ServerParse::set(const std::string &k, const std::string &v)
{
	for (std::size_t i = 0; i < K; ++i)
		if (k == properties[i])
		{
			values[i].push_back(v);
			return;
		}
}

void ServerParse::addLocation(const LocationParse &loc) { locations.push_back(loc); }
const std::vector<LocationParse> &ServerParse::getLocations() const { return locations; }

std::string ServerParse::getProperties() const
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

void ServerParse::print() const
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