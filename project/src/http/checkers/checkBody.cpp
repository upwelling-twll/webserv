#include "../AHttpRequest.hpp"

void AHttpRequest::checkBody()
{
	if (buf.size() < contentLength)
		return;
	vars["body"] = buf.substr(0, contentLength);
	buf.erase(0, contentLength);
	STATUS = READY;
}