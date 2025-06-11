#include "./HttpParser.hpp"

int main() {
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

	std::cout << "\nHost header value: " << req.getHeader("Host") << std::endl;
	return 0;
}