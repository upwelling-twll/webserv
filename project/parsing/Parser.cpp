#include "./Parser.hpp"

const char *ServersEnum[] = {
	"listen",
	"server_name",
	"root",
	"index",
	"client_max_body_size",
	"error_page"};

const char *LocationsEnum[] = {
	"path_prefix",
	"root_sd",
	"index_sd",
	"autoindex",
	"limit_except",
	"returns",
	"cgi_pass",
	"upload_store",
	"client_max_body_size_sd",
	"error_page_sd"};

Parser::Parser(const char *filename)
{
	// int isParentOpened = 0;
	// int isChildeOpened = 0;

	std::ifstream file;
	std::string line;

	std::vector<std::string> lineBuffer;

	file.open(filename);
	while (std::getline(file, line))
	{
		lineBuffer = splitAndRemoveSpaces(line);
		if(locateString(lineBuffer, "server") )
		{
			serverParser(file, line);

		}
	}
	std::getline(file, line);
	std::cout << FindChar(line, '{') << std::endl;
	file.close();
}