#ifndef SERVERPARSE_HPP
#define SERVERPARSE_HPP

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

// ───── LocationParse ────────────────────────────────────────────────
class LocationParse
{
private:
	static const std::size_t locationPropertiesRange = 11;

	static const char *properties[locationPropertiesRange];
	static const char *defaults[locationPropertiesRange]; // ← NEW

	std::vector<std::string> values[locationPropertiesRange];

public:
	LocationParse();

	bool hasProperty(const std::string &key) const;
	std::vector<std::string> get(const std::string &key) const;
	void reset(const std::string &key,
			   const std::vector<std::string> &vals);
	std::string getProperties() const;
	void print(int indent = 1) const;
};

// ───── ServerParse ─────────────────────────────────────────────────
class ServerParse
{
private:
	static const std::size_t serverPropertiesRange = 6;

	static const char *properties[serverPropertiesRange];
	static const char *defaults[serverPropertiesRange]; // ← NEW

	std::vector<std::string> values[serverPropertiesRange];
	std::vector<LocationParse> locations;

public:
	ServerParse();

	bool 						hasProperty(const std::string &key) const;
	std::vector<std::string>	get(const std::string &key) const;
	void						reset(const std::string &key,
			  						 const std::vector<std::string> &vals);
	void						addLocation(const LocationParse &loc);

	const std::vector<LocationParse> &getLocations() const;

	std::string getProperties() const;
	void		print() const;
};

#endif