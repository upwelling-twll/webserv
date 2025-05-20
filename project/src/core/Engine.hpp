#ifndef ENGINE_HPP
# define ENGINE_HPP

# include <iostream>
# include <poll.h> 

# include "../../inc/webserv.hpp"

class Config;

class Engine
{
private:
    std::vector<Socket*> _allSockets;

public:
	/*Member functions*/
    int engineRoutine(Config& config);

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
