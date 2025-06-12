#include "./HttpParser.hpp"

int main()
{
	std::string httpRequest =
		"GET /index.html HTTP/1.1\r\n"
		"Host: example.com\r\n"
		"User-Agent: TestAgent/1.0\r\n"
		"Accept: */*\r\n"
		"\r\n"
		"BODY LINE 1\r\n"
		"BODY LINE 2\r\n";

	HttpRequest req(httpRequest);
	req.print();

	// USAGE ------------------
	std::cout << req.get(METHOD) << std::endl;
	std::cout << req.get(URI) << std::endl;
	// USAGE ------------------

	return 0;
}