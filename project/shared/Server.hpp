#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <vector>
#include <string>

class Location {
private:
	std::string values[10];
	static const char* properties[10];

public:
	Location();
	~Location();

	std::string get(const std::string& key) const;
	void set(const std::string& key, const std::string& value);
};

class Server {
private:
	std::string values[6];
	static const char* properties[6];
	std::vector<Location> locations;

public:
	Server();
	~Server();

	std::string get(const std::string& key) const;
	void set(const std::string& key, const std::string& value);
};

std::ostream& operator<<(std::ostream& output_stream, Server& src);

#endif