#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

class Location
{
	static const std::size_t K = 10;
	static const char *properties[K];
	std::vector<std::string> values[K];

public:
	Location();
	bool hasProperty(const std::string &key) const;
	std::string get(const std::string &key) const;
	void set(const std::string &key, const std::string &val);
	std::string getProperties() const;
	void print(int indent = 1) const;
};

class Server
{
	static const std::size_t K = 6;
	static const char *properties[K];
	std::vector<std::string> values[K];
	std::vector<Location> locations;

public:
	Server();
	bool hasProperty(const std::string &key) const;
	std::string get(const std::string &key) const;
	void set(const std::string &key, const std::string &val);
	void addLocation(const Location &loc);
	const std::vector<Location> &getLocations() const;
	std::string getProperties() const;
	void print() const;
};

#endif