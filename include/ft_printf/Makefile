# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nipostni <awis@me.com>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/08 17:07:54 by nipostni          #+#    #+#              #
#    Updated: 2023/02/28 17:42:04 by nipostni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I include

# List of source files
SRCS =	ft_memset.c ft_bzero.c ft_memcpy.c \
		ft_memmove.c ft_memchr.c ft_memcmp.c \
		ft_strlen.c ft_isalpha.c ft_isdigit.c \
		ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_strlcpy.c \
		ft_strlcat.c ft_strnstr.c ft_atoi.c \
		ft_calloc.c ft_strdup.c ft_substr.c \
		ft_strjoin.c ft_strtrim.c ft_split.c \
		ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
		ft_putnbr_fd.c\
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
		ft_lstlast.c ft_lstadd_back.c ft_lstclear.c \
		ft_lstdelone.c ft_lstiter.c ft_lstmap.c

# List of printf source files

SRCS_PRINTF = ft_printf.c ft_printf_utils.c \

# Object files
OBJS = $(SRCS:%.c=build/%.o)
OBJS_PRINTF = $(SRCS_PRINTF:%.c=build/%.o)

# Library name
NAME = libftprintf.a

.PHONY: all clean fclean re

# Default rule: build library
all: $(NAME)

# Build library
$(NAME): $(OBJS) $(OBJS_PRINTF)
	@printf "\e[32mBuilding library...\n\e[0m"
	@ar rcs $(NAME) $(OBJS) $(OBJS_PRINTF) 
	@printf "\e[32mDone! Libft with ft_printf is ready.\n\e[0m"

# Create build directory if it does not exist
$(OBJS): | build
$(OBJS_PRINTF): | build


build:
	@mkdir -p build

# Compile source files
build/%.o: libft/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\e[36mCompiled %s successfully!\n\e[0m" $<
	
build/%.o: src/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\e[36mCompiled %s successfully!\n\e[0m" $<

# Clean object files
clean:
	@rm -f $(OBJS) $(BONUS_OBJS) $(OBJS_PRINTF)
	@printf "\e[31mObject files removed!\n\e[0m"

# Clean object files and library
fclean: clean
	@rm -f $(NAME)
	@printf "\e[31mLibrary removed!\n\e[0m"

# Full clean and rebuild
re: fclean $(NAME)
