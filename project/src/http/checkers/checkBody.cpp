#include "../AHttpRequest.hpp"

void AHttpRequest::checkBody()
{
	if (buf.size() < contentLength)
	{
		//std::cout << "||||||||||||  " << buf.size() << "  ||||||||||||  " << contentLength << "  ||||||||||||\n";
		return;
	}
	vars["body"] = buf.substr(0, contentLength);
	buf.erase(0, contentLength);
	STATUS = READY;
}