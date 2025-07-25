NAME      := webserv

# ──────────────────────────────── Компилятор ──────────────────────────────── #
CXX       := c++
CXXFLAGS  := -Wall -Wextra -Werror -g # -std=c++98

# ─────────────────────────────── Исходники ────────────────────────────────── #
SRC       := $(shell find . -type f -name '*.cpp')
OBJ       := $(SRC:.cpp=.o)

# ──────────────────────────────── Цели по умолчанию ───────────────────────── #
.PHONY: all clean fclean re run build_and_clean

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ──────────────────────────────── Уборка ───────────────────────────────────── #
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

# ─────────────────────────────── Сборка и удаление .o ──────────────────────── #
build_and_clean: $(NAME)
	@$(MAKE) clean

# ─────────────────────────────── Запуск ────────────────────────────────────── #
run:
	@if [ -f $(NAME) ]; then \
		$(MAKE) fclean; \
	fi
	$(MAKE) build_and_clean
	./$(NAME) example.conf