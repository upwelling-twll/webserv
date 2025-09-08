#include "Rest.hpp"
#include <sstream>
#include <ctime>
#include <fstream>
#include <cstdio>
#include <cerrno>
#include <cstdlib>

Rest::Rest() : storageDir(".") {}
Rest::Rest(const std::string &dir) : storageDir(dir) {}

void Rest::setStorageDir(const std::string &dir) { storageDir = dir; }

struct PathParts {
    std::string directory;
    std::string filename;
};

PathParts splitUri(const std::string& uri) {
    PathParts parts;
    if (uri.empty() || uri == "/") {
        parts.directory = "/";
        parts.filename = "";
        return parts;
    }
    size_t pos = uri.find_last_of('/');
    if (pos == std::string::npos) {
        parts.directory = "/";
        parts.filename = uri;
    } else {
        parts.directory = uri.substr(0, pos + 1);   // keep trailing slash
        parts.filename = uri.substr(pos + 1);
    }
    return parts;
}

int validateRequest(AHttpRequest& req, const Server& srv, const std::string& method, const Location*& outLoc)
{
	std::string uri = req.get(URI);
	outLoc = srv.matchLocation(uri);

	if (!outLoc)
	{
		return 404; // no location matched
	}
	if (!outLoc->isMethodAllowed(method))
	{
		return 405; // method not allowed
	}
	if (method == "POST")
	{
		size_t bodySize = req.get(BODY).size();
		if (bodySize > outLoc->getMaxBodySize())
		{
		return 413; // Payload Too Large
		}
	}
	return 200; // OK
}
std::string Rest::get(AHttpRequest &req, int status, Config& conf)
{
	Headers h;
	h["Content-Type"] = "text/html; charset=utf-8";

	std::cout << "DEBUG: " << safeHeader(req, HOST) << std::endl;
	const Server& srv = conf.matchServer(safeHeader(req, HOST));
	const Location* loc;
	int vstatus = validateRequest(req, srv, "GET", loc);
	if (vstatus != 200)
		return formResponse(req, vstatus, reasonPhrase(vstatus), h);

	PathParts parts = splitUri(req.get(URI));
	std::cout << "DEBUG: root_sd = " << loc->getRoot_sd()<< std::endl;
	std::string filepath = loc->getRoot_sd() + parts.directory + parts.filename;

	std::cout << "DEBUG: filepath = " << filepath << std::endl;
	std::ifstream ifs(filepath.c_str());
    if (!ifs)
        return formResponse(req, 404, "<h1>Not Found</h1>", h);

    std::ostringstream buffer;
    buffer << ifs.rdbuf();
    return formResponse(req, status, buffer.str(), h);
}

std::string Rest::post(AHttpRequest &req, int status, Config& conf)
{
	(void)conf;

	std::string body = req.get(BODY);
	std::string name = generateTxtName();
	std::string path = storageDir + "/" + name;

	int s = status;
	{
		std::ofstream ofs(path.c_str(), std::ios::out | std::ios::binary);
		if (!ofs)
			s = 500;
		else
		{
			ofs.write(body.data(), static_cast<std::streamsize>(body.size()));
			if (!ofs.good())
				s = 500;
		}
	}

	Headers h;
	h["Content-Type"] = "text/plain; charset=utf-8";
	std::string outBody = (s == 500) ? "Save error\n" : ("Saved: " + name + "\n");
	return formResponse(req, s, outBody, h);
}

std::string Rest::del(AHttpRequest &req, int status, const std::string &filename, Config& conf)
{
	(void)conf;

	std::string path = storageDir + "/" + filename;
	int s = status;

	if (std::remove(path.c_str()) != 0)
	{
		if (errno == ENOENT)
			s = 404;
		else
			s = 500;
	}

	Headers h;
	h["Content-Type"] = "text/plain; charset=utf-8";
	std::string outBody;
	if (s == 404)
		outBody = "Not found\n";
	else if (s == 500)
		outBody = "Delete error\n";
	else
		outBody = "Deleted: " + filename + "\n";

	return formResponse(req, s, outBody, h);
}

std::string Rest::formResponse(AHttpRequest &req,
							   int status,
							   const std::string &body,
							   Headers headers)
{
	std::string httpVersion = safeHttpVersion(req);

	if (headers.find("Date") == headers.end())
		headers["Date"] = currentTime();

	if (headers.find("Connection") == headers.end())
	{
		std::string conn = safeHeader(req, CONNECTION);
		headers["Connection"] = conn.empty() ? "close" : conn;
	}

	if (headers.find("Content-Type") == headers.end())
		headers["Content-Type"] = "text/plain; charset=utf-8";

	{
		std::ostringstream ss;
		ss << body.size();
		headers["Content-Length"] = ss.str();
	}

	std::ostringstream out;
	out << httpVersion << " " << status << " " << reasonPhrase(status) << "\r\n";

	Headers::const_iterator it = headers.begin();
	for (; it != headers.end(); ++it)
		out << it->first << ": " << it->second << "\r\n";

	out << "\r\n"
		<< body;
	return out.str();
}

const char *Rest::reasonPhrase(int code)
{
	switch (code)
	{
	case 200:
		return "OK";
	case 201:
		return "Created";
	case 202:
		return "Accepted";
	case 204:
		return "No Content";
	case 301:
		return "Moved Permanently";
	case 302:
		return "Found";
	case 304:
		return "Not Modified";
	case 400:
		return "Bad Request";
	case 401:
		return "Unauthorized";
	case 403:
		return "Forbidden";
	case 404:
		return "Not Found";
	case 405:
		return "Method Not Allowed";
	case 409:
		return "Conflict";
	case 413:
		return "Payload Too Large";
	case 415:
		return "Unsupported Media Type";
	case 500:
		return "Internal Server Error";
	case 501:
		return "Not Implemented";
	case 503:
		return "Service Unavailable";
	default:
		return "Unknown";
	}
}

std::string Rest::currentTime()
{
	std::time_t t = std::time(NULL);
	std::tm gm;
	std::tm *gmp = std::gmtime(&t);
	if (gmp)
		gm = *gmp;
	char buf[64];
	std::strftime(buf, sizeof(buf), "%a, %d %b %Y %H:%M:%S GMT", &gm);
	return std::string(buf);
}

std::string Rest::safeHeader(AHttpRequest &req, HeaderKey key)
{
	return req.get(key);
}

std::string Rest::safeHttpVersion(AHttpRequest &req)
{
	std::string v = req.get(VERSION);
	if (v.empty())
		return "HTTP/1.1";
	if (v.size() >= 5 && v.substr(0, 5) == "HTTP/")
		return v;
	return std::string("HTTP/") + v;
}

std::string Rest::generateTxtName()
{
	std::ostringstream ss;
	ss << std::time(NULL) << "_" << (std::rand() % 1000000) << ".txt";
	return ss.str();
}