#include "../Setters.hpp"
int setErrorPage(Server &instance, std::vector<std::string> buffer)
{
	instance.setErrorPage(buffer[0]);
	return 0;
}