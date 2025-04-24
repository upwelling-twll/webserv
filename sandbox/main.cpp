
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <poll.h>
#include <unistd.h>
#include <dirent.h>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <stdexcept>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>

#define BUFFER_SIZE 8192
#define DEFAULT_PORT 8080
#define DEFAULT_ROOT "./www"

struct ServerConfig
{
	int port;
	std::string root;
	size_t client_max_body;
	std::string index;
	ServerConfig() : port(DEFAULT_PORT), root(DEFAULT_ROOT), client_max_body(1 << 20), index("index.html") {}
};

static ServerConfig parseConfig(const char *path)
{
	ServerConfig conf;
	std::ifstream in(path);
	if (!in)
		throw std::runtime_error("Unable to open config");
	std::string line, key, value;
	while (std::getline(in, line))
	{
		std::istringstream ss(line);
		if (!(ss >> key >> value))
			continue;
		if (key == "listen")
			conf.port = std::atoi(value.c_str());
		else if (key == "root")
			conf.root = value;
		else if (key == "client_max_body")
			conf.client_max_body = std::atoi(value.c_str());
		else if (key == "index")
			conf.index = value;
	}
	return conf;
}

static int set_nonblocking(int fd)
{
	int f = fcntl(fd, F_GETFL, 0);
	return f < 0 ? -1 : fcntl(fd, F_SETFL, f | O_NONBLOCK);
}
static std::string http_status(int c)
{
	switch (c)
	{
	case 200:
		return "OK";
	case 201:
		return "Created";
	case 204:
		return "No Content";
	case 400:
		return "Bad Request";
	case 404:
		return "Not Found";
	case 413:
		return "Payload Too Large";
	case 500:
		return "Internal Server Error";
	default:
		return "Error";
	}
}
static void send_response(int fd, int code, const std::string &body, const std::string &ct = "text/plain")
{
	std::ostringstream s;
	s << "HTTP/1.1 " << code << ' ' << http_status(code) << "\r\n";
	s << "Content-Length: " << body.size() << "\r\n";
	s << "Content-Type: " << ct << "\r\nConnection: close\r\n\r\n"
	  << body;
	::send(fd, s.str().c_str(), s.str().size(), 0);
}

static void serve_file(int fd, const std::string &path)
{
	int file = ::open(path.c_str(), O_RDONLY);
	if (file < 0)
	{
		send_response(fd, 404, "404 Not Found");
		return;
	}
	struct stat st;
	fstat(file, &st);
	std::vector<char> buf(st.st_size);
	read(file, &buf[0], st.st_size);
	close(file);
	send_response(fd, 200, std::string(buf.begin(), buf.end()), "text/html");
}

static void handle_get(int fd, const ServerConfig &conf, const std::string &urlPath)
{
	std::string path = conf.root + urlPath;
	struct stat st;
	if (stat(path.c_str(), &st) < 0)
	{
		send_response(fd, 404, "404 Not Found");
		return;
	}
	if (S_ISDIR(st.st_mode))
	{
		if (path[path.size() - 1] != '/')
			path += "/";
		path += conf.index;
		if (stat(path.c_str(), &st) < 0)
		{
			send_response(fd, 404, "404 Not Found");
			return;
		}
	}
	serve_file(fd, path);
}

static void handle_delete(int fd, const ServerConfig &conf, const std::string &urlPath)
{
	std::string path = conf.root + urlPath;
	if (::unlink(path.c_str()) == 0)
		send_response(fd, 204, "");
	else
		send_response(fd, 404, "File Not Found");
}

static void handle_post(int fd, const ServerConfig &conf, const std::string &urlPath, const std::string &body)
{
	if (body.size() > conf.client_max_body)
	{
		send_response(fd, 413, "Payload Too Large");
		return;
	}
	std::string out = conf.root + urlPath;
	int file = ::open(out.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file < 0)
	{
		send_response(fd, 500, "Cannot save");
		return;
	}
	::write(file, body.c_str(), body.size());
	::close(file);
	send_response(fd, 201, "Created");
}

static void process_request(int fd, const ServerConfig &conf, const std::string &req)
{
	std::istringstream s(req);
	std::string method, target, version;
	s >> method >> target >> version;
	if (method == "GET")
		handle_get(fd, conf, target);
	else if (method == "DELETE")
		handle_delete(fd, conf, target);
	else if (method == "POST")
	{
		size_t pos = req.find("\r\n\r\n");
		std::string body;
		if (pos != std::string::npos)
			body = req.substr(pos + 4);
		handle_post(fd, conf, target, body);
	}
	else
		send_response(fd, 400, "Bad Request");
}

int main(int argc, char **argv)
{
	ServerConfig conf;
	try
	{
		conf = parseConfig(argc > 1 ? argv[1] : "default.conf");
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	int lfd = socket(AF_INET, SOCK_STREAM, 0);
	if (lfd < 0)
	{
		perror("socket");
		return 1;
	}
	int yes = 1;
	setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
	set_nonblocking(lfd);
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(conf.port);
	if (bind(lfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("bind");
		return 1;
	}
	if (listen(lfd, 128) < 0)
	{
		perror("listen");
		return 1;
	}
	std::vector<struct pollfd> fds;
	fds.push_back((struct pollfd){lfd, POLLIN, 0});
	std::map<int, std::string> buf;
	while (true)
	{
		if (poll(&fds[0], fds.size(), -1) < 0)
		{
			if (errno == EINTR)
				continue;
			perror("poll");
			break;
		}
		for (size_t i = 0; i < fds.size(); ++i)
		{
			if (!fds[i].revents)
				continue;
			if (fds[i].fd == lfd)
			{
				int c;
				while ((c = accept(lfd, NULL, NULL)) >= 0)
				{
					set_nonblocking(c);
					fds.push_back((struct pollfd){c, POLLIN, 0});
				}
			}
			else if (fds[i].revents & POLLIN)
			{
				char tmp[BUFFER_SIZE];
				ssize_t n = recv(fds[i].fd, tmp, BUFFER_SIZE, 0);
				if (n <= 0)
				{
					close(fds[i].fd);
					fds.erase(fds.begin() + i);
					--i;
					continue;
				}
				buf[fds[i].fd].append(tmp, n);
				if (buf[fds[i].fd].find("\r\n\r\n") != std::string::npos)
				{
					process_request(fds[i].fd, conf, buf[fds[i].fd]);
					close(fds[i].fd);
					buf.erase(fds[i].fd);
					fds.erase(fds.begin() + i);
					--i;
				}
			}
		}
	}
	return 0;
}