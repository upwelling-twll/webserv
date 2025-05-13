#include "Server.hpp"

const char* Location::properties[10] = {
	"path_prefix", "root_sd", "index_sd", "autoindex", "limit_except",
	"returns", "cgi_pass", "upload_store", "client_max_body_size_sd", "error_page_sd"
};

const char* Server::properties[6] = {
	"listen", "server_name", "root", "index", "client_max_body_size", "error_page"
};

Location::Location() {
	values[0] = "-";
	values[1] = "server_default";
	values[2] = "server_default";
	values[3] = "off";
	values[4] = "GET POST DELETE HEAD";
	values[5] = "";
	values[6] = "off";
	values[7] = "forbidden";
	values[8] = "server_default";
	values[9] = "server_default";
}

Location::~Location() {}

std::string Location::get(const std::string& key) const {
	for (int i = 0; i < 10; ++i) {
		if (key == properties[i])
			return values[i];
	}
	return "";
}

void Location::set(const std::string& key, const std::string& value) {
	for (int i = 0; i < 10; ++i) {
		if (key == properties[i]) {
			values[i] = value;
			return;
		}
	}
}

Server::Server() {
	values[0] = "80";
	values[1] = "";
	values[2] = "";
	values[3] = "index.html";
	values[4] = "1MB";
	values[5] = "";
}

Server::~Server() {}

std::string Server::get(const std::string& key) const {
	for (int i = 0; i < 6; ++i) {
		if (key == properties[i])
			return values[i];
	}
	return "";
}

void Server::set(const std::string& key, const std::string& value) {
	for (int i = 0; i < 6; ++i) {
		if (key == properties[i]) {
			values[i] = value;
			return;
		}
	}
}