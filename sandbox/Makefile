# To build: run `make`
# Requires C++98 compiler

NAME=webserv
CXX=c++
CXXFLAGS=-Wall -Wextra -Werror -std=c++98
SRC=main.cpp
OBJ=$(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all