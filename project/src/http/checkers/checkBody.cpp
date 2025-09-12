#include "../AHttpRequest.hpp"

void AHttpRequest::checkBody()
{
	// std::cout << "buf.size()=" << buf.size() << ", content-length=" << contentLength << std::endl;
	if (buf.size() < contentLength)
	{
		//std::cout << "||||||||||||  " << buf.size() << "  ||||||||||||  " << contentLength << "  ||||||||||||\n";
		return;
	}
	if (buf.size() > contentLength)
        buf.erase(0, buf.size() - contentLength);
	std::cout << "DEBUG: buf in checkBody() " << buf << std::endl;
	vars["body"] = buf.substr(0, contentLength);
	std::cout << "DEBUG: body received: " << vars["body"] << std::endl;

	if (vars["method"] == "POST" && headers["Content-Type"].find("multipart/form-data") != std::string::npos)
	{
		std::string fileData = extractMultipartFile();
		std::cout << "DEBUG: extracted file content:\n" << fileData << std::endl;
		vars["body"] = fileData;
	}

	buf.erase(0, contentLength);
	STATUS = READY;
}