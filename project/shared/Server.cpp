#include "Server.hpp"
#include <iomanip>   // только если нужен std::setw, не обязательно

// ───── Static Tables ────────────────────────────────────
const char* Location::properties[Location::locationPropertiesRange] = {
    "path_prefix", "root", "index_sd", "autoindex", "limit_except",
    "return", "cgi_pass", "upload_store", "client_max_body_size_sd", "error_page_sd"};

const char* Location::defaults[Location::locationPropertiesRange] = {
    "-", "server_default", "server_default", "off", "GET POST DELETE HEAD",
    "",  "off", "forbidden", "server_default", "server_default"};

const char* Server::properties[Server::serverPropertiesRange] = {
    "listen", "server_name", "root", "index", "client_max_body_size", "error_page"};

const char* Server::defaults[Server::serverPropertiesRange] = {
    "80", "", "", "index.html", "1MB", ""};

// ───── Location ──────────────────────────────────────────
Location::Location()
{
    for (std::size_t i = 0; i < locationPropertiesRange; ++i)
        values[i].push_back(defaults[i]);
}

bool Location::hasProperty(const std::string& k) const
{
    for (std::size_t i = 0; i < locationPropertiesRange; ++i)
        if (k == properties[i]) return true;
    return false;
}

std::vector<std::string> Location::get(const std::string& k) const
{
    for (std::size_t i = 0; i < locationPropertiesRange; ++i)
        if (k == properties[i]) return values[i];
    return std::vector<std::string>();
}

void Location::reset(const std::string& k, const std::vector<std::string>& v)
{
    for (std::size_t i = 0; i < locationPropertiesRange; ++i)
        if (k == properties[i]) { values[i] = v; return; }
}

std::string Location::getProperties() const
{
    std::ostringstream os;
    for (std::size_t i = 0; i < locationPropertiesRange; ++i)
        os << (i ? " " : "") << properties[i];
    return os.str();
}

void Location::print(int indent) const
{
    std::string pad(indent * 2, ' ');
    std::cout << pad << "location {\n";
    for (std::size_t i = 0; i < locationPropertiesRange; ++i)
    {
        const std::string& cur = values[i].empty() ? "" : values[i].back();
        bool changed = cur != defaults[i];                       // ← NEW
        std::cout << pad << "  " << properties[i] << ": "
                  << (changed ? "\033[32m" : "\033[33m")
                  << (cur.empty() ? "<unset>" : cur)
                  << "\033[0m\n";
    }
    std::cout << pad << "}\n";
}

// ───── Server ────────────────────────────────────────────
Server::Server()
{
    for (std::size_t i = 0; i < serverPropertiesRange; ++i)
        values[i].push_back(defaults[i]);
}

bool Server::hasProperty(const std::string& k) const
{
    for (std::size_t i = 0; i < serverPropertiesRange; ++i)
        if (k == properties[i]) return true;
    return false;
}

std::vector<std::string> Server::get(const std::string& k) const
{
    for (std::size_t i = 0; i < serverPropertiesRange; ++i)
        if (k == properties[i]) return values[i];
    return std::vector<std::string>();
}

void Server::reset(const std::string& k, const std::vector<std::string>& v)
{
    for (std::size_t i = 0; i < serverPropertiesRange; ++i)
        if (k == properties[i]) { values[i] = v; return; }
}

void Server::addLocation(const Location& loc) { locations.push_back(loc); }
const std::vector<Location>& Server::getLocations() const { return locations; }

std::string Server::getProperties() const
{
    std::ostringstream os;
    for (std::size_t i = 0; i < serverPropertiesRange; ++i)
        os << (i ? " " : "") << properties[i];
    return os.str();
}

void Server::print() const
{
    std::cout << "server {\n";
    for (std::size_t i = 0; i < serverPropertiesRange; ++i)
    {
        const std::string& cur = values[i].empty() ? "" : values[i].back();
        bool changed = cur != defaults[i];                       // ← NEW
        std::cout << "  " << properties[i] << ": "
                  << (changed ? "\033[32m" : "\033[33m")
                  << (cur.empty() ? "<unset>" : cur)
                  << "\033[0m\n";
    }
    for (std::size_t j = 0; j < locations.size(); ++j)
        locations[j].print(2);
    std::cout << "}\n";
}