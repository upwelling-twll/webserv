#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

// ───── Location ────────────────────────────────────────────────
class Location
{
private:
	static const std::size_t locationPropertiesRange = 10;

	static const char *properties[locationPropertiesRange];
	static const char *defaults[locationPropertiesRange]; // ← NEW

	std::vector<std::string> values[locationPropertiesRange];

public:
	Location();

	bool hasProperty(const std::string &key) const;
	std::vector<std::string> get(const std::string &key) const;
	void reset(const std::string &key,
			   const std::vector<std::string> &vals);
	std::string getProperties() const;
	void print(int indent = 1) const;
};

// ───── Server ─────────────────────────────────────────────────
class Server
{
private:
	static const std::size_t serverPropertiesRange = 6;

	static const char *properties[serverPropertiesRange];
	static const char *defaults[serverPropertiesRange]; // ← NEW

	std::vector<std::string> values[serverPropertiesRange];
	std::vector<Location> locations;

public:
	Server();

	bool hasProperty(const std::string &key) const;
	std::vector<std::string> get(const std::string &key) const;
	void reset(const std::string &key,
			   const std::vector<std::string> &vals);
	void addLocation(const Location &loc);

	const std::vector<Location> &getLocations() const;

	std::string getProperties() const;
	void print() const;
};

#endif