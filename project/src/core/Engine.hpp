#ifndef ENGINE_HPP
# define ENGINE_HPP

# include <iostream>
# include <poll.h> 

# include "../../inc/webserv.hpp"

class Config;
class Connection;

class Engine
{
private:
    std::vector<Socket*> 		_allSockets;
	std::vector<Connection>		_allConnections;
	std::vector<struct pollfd>	_fds;

public:
	/*Member functions*/
    int 			engineRoutine(Config& config);
	void			polloutSocketsHandle(size_t i,
											std::map<const Socket*, Connection*>& activeConnections);
	void			pollinSocketsHandle(size_t i,
											std::map<const Socket*, Connection*>& activeConnections);

	struct pollfd	createPollFd(int fd, short events, short revents);

	/*Getters and Setters*/

	/*Constructors*/
    Engine(std::vector<Socket*> allSockets);
	// Engine(void);

	/*Destructors*/
    ~Engine( void );

	/*Overload operators*/
	Engine &operator=(const Engine& src);
};

// std::ostream& operator<<(std::ostream &output_stream, Engine& src);

#endif // Engine_HPP
