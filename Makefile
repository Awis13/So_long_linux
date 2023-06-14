CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./include -I./include/ft_printf -I./include/get_next_line
SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)
LIBS = -L./mlx -lmlx -lX11 -lXext

NAME = so_long

all: $(NAME)

$(NAME): $(OBJS) include/get_next_line/get_next_line.o include/ft_printf/libftprintf.a
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS) include/get_next_line/get_next_line.o include/ft_printf/libftprintf.a $(LIBS)
	@echo "\033[0;35m  ____           _                      "
	@echo "\033[0;35m / ___|  ___    | |    ___  _ __   __ _ "
	@echo "\033[0;35m \\___ \\ / _ \\   | |   / _ \\| '_ \\ / _\` |"
	@echo "\033[0;35m  ___) | (_) |  | |__| (_) | | | | (_| |"
	@echo "\033[0;35m |____/ \\___/___|_____\\___/|_| |_|\__, |"
	@echo "\033[0;35m           |_____|                |___/ "
	@echo "\033[0;35mBuild successful! Run the game with './$(NAME)'\033[0m"

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

include/ft_printf/libftprintf.a:
	make -C include/ft_printf

include/get_next_line/get_next_line.o: include/get_next_line/get_next_line.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJS) include/get_next_line/get_next_line.o
	make -C include/ft_printf clean

.PHONY: fclean
fclean: clean
	rm -f $(NAME)
	make -C include/ft_printf fclean

.PHONY: re
re: fclean all
