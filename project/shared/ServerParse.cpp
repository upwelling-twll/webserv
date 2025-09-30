#include "ServerParse.hpp"
#include <iomanip>   // только если нужен std::setw, не обязательно

// ───── Static Tables ────────────────────────────────────
const char* LocationParse::properties[LocationParse::locationPropertiesRange] = {
    "path_prefix", "root", "index_sd", "autoindex", "limit_except",
    "return", "cgi_pass", "upload_store", "client_max_body_size_sd", "error_page_sd", "proxy_pass"};

const char* LocationParse::defaults[LocationParse::locationPropertiesRange] = {
    "-", "server_default", "server_default", "off", "GET POST DELETE HEAD",
    "",  "off", "forbidden", "1MB", "server_default", ""};

const char* ServerParse::properties[ServerParse::serverPropertiesRange] = {
    "listen", "server_name", "root", "index", "client_max_body_size", "error_page"};

const char* ServerParse::defaults[ServerParse::serverPropertiesRange] = {
    "80", "", "", "index.html", "1MB", ""};

// ───── Location ──────────────────────────────────────────
// LocationParse::LocationParse()
// {
//     for (std::size_t i = 0; i < locationPropertiesRange; ++i)
//         values[i].push_back(defaults[i]);
// }

// bool LocationParse::hasProperty(const std::string& k) const
// {
//     for (std::size_t i = 0; i < locationPropertiesRange; ++i)
//         if (k == properties[i]) return true;
//     return false;
// }

// std::vector<std::string> LocationParse::get(const std::string& k) const
// {
//     for (std::size_t i = 0; i < locationPropertiesRange; ++i)
//         if (k == properties[i]) return values[i];
//     return std::vector<std::string>();
// }

// void LocationParse::reset(const std::string& k, const std::vector<std::string>& v)
// {
//     for (std::size_t i = 0; i < locationPropertiesRange; ++i)
//         if (k == properties[i]) { values[i] = v; return; }
// }

// std::string LocationParse::getProperties() const
// {
//     std::ostringstream os;
//     for (std::size_t i = 0; i < locationPropertiesRange; ++i)
//         os << (i ? " " : "") << properties[i];
//     return os.str();
// }

// void LocationParse::print(int indent) const
// {
//     std::string pad(indent * 2, ' ');
//     std::cout << pad << "location {\n";
//     for (std::size_t i = 0; i < locationPropertiesRange; ++i)
//     {
//         const std::string& cur = values[i].empty() ? "" : values[i].back();
//         bool changed = cur != defaults[i];                       // ← NEW
//         std::cout << pad << "  " << properties[i] << ": "
//                   << (changed ? "\033[32m" : "\033[33m")
//                   << (cur.empty() ? "<unset>" : cur)
//                   << "\033[0m\n";
//     }
//     std::cout << pad << "}\n";
// }

LocationParse::LocationParse()
{
    for (std::size_t i = 0; i < locationPropertiesRange; ++i)
        values[i].push_back(defaults[i]);
}

bool LocationParse::hasProperty(const std::string& k) const
{
    for (std::size_t i = 0; i < locationPropertiesRange; ++i)
        if (k == properties[i]) return true;
    return false;
}

std::vector<std::string> LocationParse::get(const std::string& k) const
{
    for (std::size_t i = 0; i < locationPropertiesRange; ++i)
        if (k == properties[i]) return values[i];
    return std::vector<std::string>();
}

void LocationParse::reset(const std::string& k, const std::vector<std::string>& v)
{
    if (k == "error_page_sd") {
        addErrorPage(v);
        return;
    }

    for (std::size_t i = 0; i < locationPropertiesRange; ++i)
        if (k == properties[i]) { values[i] = v; return; }
}

void LocationParse::append(const std::string& k, const std::vector<std::string>& v)
{
    if (k == "error_page_sd") {
        addErrorPage(v);
        return;
    }

    for (std::size_t i = 0; i < locationPropertiesRange; ++i)
        if (k == properties[i]) {
            values[i].insert(values[i].end(), v.begin(), v.end());
            return;
        }
}

void LocationParse::addErrorPage(const std::vector<std::string>& vals)
{
    if (vals.size() < 2)
        return; // need at least codes + path

    std::string path = vals.back();
    for (size_t i = 0; i < vals.size() - 1; ++i) {
        int code = std::atoi(vals[i].c_str());
        if (code > 0)
            errorPages[code] = path;
    }
}

void LocationParse::addMissingErrorPage(int statusCode, std::string path)
{
    this->errorPages.insert(std::pair<const int, std::string>(statusCode, path));
}

const std::map<int, std::string>& LocationParse::getErrorPages() const 
{
    std::cout << "returning error pages, size=" << errorPages.size() << std::endl;
    return errorPages;
}

std::string LocationParse::getProperties() const
{
    std::ostringstream os;
    for (std::size_t i = 0; i < locationPropertiesRange; ++i)
        os << (i ? " " : "") << properties[i];
    return os.str();
}

void LocationParse::print(int indent) const
{
    std::string pad(indent * 2, ' ');
    std::cout << pad << "location {\n";
    for (std::size_t i = 0; i < locationPropertiesRange; ++i)
    {
        if (std::string(properties[i]) == "error_page_sd")
            continue; // printed separately below

        const std::string& cur = values[i].empty() ? "" : values[i].back();
        bool changed = cur != defaults[i];
        std::cout << pad << "  " << properties[i] << ": "
                  << (changed ? "\033[32m" : "\033[33m")
                  << (cur.empty() ? "<unset>" : cur)
                  << "\033[0m\n";
    }

    // Print error_page mapping
    for (std::map<int,std::string>::const_iterator it = errorPages.begin();
         it != errorPages.end(); ++it)
    {
        std::cout << pad << "  error_page_sd " << it->first
                  << " → " << it->second << "\n";
    }

    std::cout << pad << "}\n";
}


// ───── Server ────────────────────────────────────────────
ServerParse::ServerParse()
{
    for (std::size_t i = 0; i < serverPropertiesRange; ++i)
        values[i].push_back(defaults[i]);
}

bool ServerParse::hasProperty(const std::string& k) const
{
    for (std::size_t i = 0; i < serverPropertiesRange; ++i)
        if (k == properties[i]) return true;
    return false;
}

std::vector<std::string> ServerParse::get(const std::string& k) const
{
    for (std::size_t i = 0; i < serverPropertiesRange; ++i)
        if (k == properties[i]) return values[i];
    return std::vector<std::string>();
}

void ServerParse::reset(const std::string& k, const std::vector<std::string>& v)
{
    if (k == "error_page") {
        addErrorPage(v); // store properly
        return;
    }

    for (std::size_t i = 0; i < serverPropertiesRange; ++i)
        if (k == properties[i]) { values[i] = v; return; }
}

void ServerParse::append(const std::string& k, const std::vector<std::string>& v)
{
    if (k == "error_page") {
        addErrorPage(v); // add again
        return;
    }

    for (std::size_t i = 0; i < serverPropertiesRange; ++i)
        if (k == properties[i]) {
            values[i].insert(values[i].end(), v.begin(), v.end());
            return;
        }
}


// void ServerParse::reset(const std::string& k, const std::vector<std::string>& v)
// {
//     for (std::size_t i = 0; i < serverPropertiesRange; ++i)
//         if (k == properties[i]) { values[i] = v; return; }
// }

void ServerParse::addErrorPage(const std::vector<std::string>& vals)
{
    if (vals.size() < 2) return; // must have codes + path

    std::string path = vals.back();
    for (size_t i = 0; i < vals.size() - 1; ++i) {
        int code = std::atoi(vals[i].c_str());
        if (code > 0)
            errorPages[code] = path;
    }
}

const std::map<int, std::string>& ServerParse::getErrorPages() const
{
    return errorPages;
}


void ServerParse::addLocation(const LocationParse& loc)
{
    locations.push_back(loc);
}

const std::vector<LocationParse>& ServerParse::getLocations() const
{ 
    return locations;
}

// std::vector<LocationParse>& ServerParse::getLocationsToEdit()
// { 
//     return locations;
// }

const std::vector<LocationParse>& ServerParse::getLocationsToEdit() const
{ 
    return locations;
}

std::string ServerParse::getProperties() const
{
    std::ostringstream os;
    for (std::size_t i = 0; i < serverPropertiesRange; ++i)
        os << (i ? " " : "") << properties[i];
    return os.str();
}

// void ServerParse::print() const
// {
//     std::cout << "server {\n";
//     for (std::size_t i = 0; i < serverPropertiesRange; ++i)
//     {
//         const std::string& cur = values[i].empty() ? "" : values[i].back();
//         bool changed = cur != defaults[i];
//         std::cout << "  " << properties[i] << ": "
//                   << (changed ? "\033[32m" : "\033[33m")
//                   << (cur.empty() ? "<unset>" : cur)
//                   << "\033[0m\n";
//     }
//     for (std::size_t j = 0; j < locations.size(); ++j)
//         locations[j].print(2);
//     std::cout << "}\n";
// }

void ServerParse::print() const
{
    std::cout << "server {\n";
    for (std::size_t i = 0; i < serverPropertiesRange; ++i)
    {
        const std::string& cur = values[i].empty() ? "" : values[i].back();
        bool changed = cur != defaults[i];
        if (std::string(properties[i]) == "error_page")
            continue; // handled below

        std::cout << "  " << properties[i] << ": "
                  << (changed ? "\033[32m" : "\033[33m")
                  << (cur.empty() ? "<unset>" : cur)
                  << "\033[0m\n";
    }

    // print error_page map
    for (std::map<int,std::string>::const_iterator it = errorPages.begin();
         it != errorPages.end(); ++it)
    {
        std::cout << "  error_page " << it->first << " → " << it->second << "\n";
    }

    for (std::size_t j = 0; j < locations.size(); ++j)
        locations[j].print(2);

    std::cout << "}\n";
}
