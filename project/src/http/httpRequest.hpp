#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

# include <iostream>

class httpRequest
{
private:
    // Add member variables here

public:
	/*Member functions*/
    void method();

	/*Getters and Setters*/

	/*Constructors*/
    httpRequest(/*Parameterized Constructor*/);
	httpRequest(void);

	/*Destructors*/
    ~httpRequest( void );

	/*Overload operators*/
	httpRequest &operator=(const httpRequest& src);
};

std::ostream& operator<<(std::ostream &output_stream, httpRequest& src);

#endif // HTTPREQUEST_HPP
