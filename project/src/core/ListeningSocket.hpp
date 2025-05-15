#ifndef LISTENINGSOCKET_HPP
# define LISTENINGSOCKET_HPP

# include <iostream>

class ListeningSocket : public Socket
{
private:
    bool		_listening;
	int			_port;
	std::string	_ip;

public:
	/*Member functions*/
	virtual bool	isListening() const;
    void			handle();

	/*Getters and Setters*/

	/*Constructors*/
    ListeningSocket(int fd);

	/*Destructors*/
    ~ListeningSocket( void );

	/*Overload operators*/
	ListeningSocket &operator=(const ListeningSocket& src);
};

std::ostream& operator<<(std::ostream &output_stream, ListeningSocket& src);

#endif // LISTENINGSOCKET_HPP
