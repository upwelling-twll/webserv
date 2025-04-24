 #!/bin/bash

# Get the class name from the first argument
classname=$1
uppercase_classname=$(echo "$classname" | tr '[:lower:]' '[:upper:]')

# Create the .hpp file
cat > "${classname}.hpp" <<EOL
#ifndef ${uppercase_classname}_HPP
# define ${uppercase_classname}_HPP

# include <iostream>

class ${classname}
{
private:
    // Add member variables here

public:
	/*Member functions*/
    void method();

	/*Getters and Setters*/

	/*Constructors*/
    ${classname}(/*Parameterized Constructor*/);
	${classname}(void);

	/*Destructors*/
    ~$classname( void );

	/*Overload operators*/
	${classname} &operator=(const ${classname}& src);
};

std::ostream& operator<<(std::ostream &output_stream, ${classname}& src);

#endif // ${uppercase_classname}_HPP
EOL

# Create the .cpp file
cat > "${classname}.cpp" <<EOL
#include "${classname}.hpp"

/*Member functions*/
void ${classname}::method()
{
    // Method implementation
}

/*Getters and Setters*/

/*Constructors*/
${classname}::${classname}(/*Parameterized Constructor*/)
{
   std::cout << "${classname} parameterized constructor is called" << std::endl;
}

${classname}::${classname}()
{
    std::cout << "${classname} default constructor is called" << std::endl;
}

/*Destructors*/
${classname}::~${classname}( void )
{
    std::cout << "${classname} destructor is called" << std::endl;
}

/*Overload operators*/
${classname}& ${classname}::operator=(const ${classname}& src)
{
	std::cout << "${classname} copy assignment is called" << std::endl;
	if (this != &src)
	{
		// Assinment variables
	}
	return (*this);
}

std::ostream& operator<<(std::ostream& output_stream, ${classname}& src)
{
	output_stream << "* ${classname} Class info*" << std::endl;
	return output_stream;
}

EOL

echo "Class ${classname} created with ${classname}.hpp and ${classname}.cpp"
