# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: walnaimi <walnaimi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/29 17:03:00 by sataskin          #+#    #+#              #
#    Updated: 2024/12/19 20:23:09 by walnaimi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    := trace
CC      := gcc
CFLAGS  := -Wextra -Wall -Werror -Ofast
LIBMLX  := ./MLX42

# Include headers and libraries
HEADERS := -I ./include -I $(LIBMLX)/include
LIBS    := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

# Source and object files
SRCS    :=	main.c \
			vector.c \
			raytracer.c \
			plane.c
OBJS    := $(SRCS:.c=.o)

# Default target
all: libmlx $(NAME)

# # Build the MLX42 library
# libmlx:
# 	@cmake -B $(LIBMLX)/build $(LIBMLX) && cmake --build $(LIBMLX)/build -j4

# Check if MLX42 exists, else install it
libmlx:
	@if [ ! -d "$(LIBMLX)" ]; then \
		echo "MLX42 not found, installing..."; \
		git clone https://github.com/codam-coding-college/MLX42 $(LIBMLX); \
	fi
	@cmake -B $(LIBMLX)/build $(LIBMLX) && cmake --build $(LIBMLX)/build -j4

# Compile object files
%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ && \
		printf "Compiling: $(notdir $<)\n"

# Link the final binary
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $@ && \
		printf "Linking: $(NAME)\n"

# Clean object files and library builds
clean:
	@rm -f $(OBJS)
	@rm -rf $(LIBMLX)/build

# Clean everything, including the binary
fclean: clean
	@rm -f $(NAME)
	@rm -rdf MLX42

# Rebuild from scratch
re: fclean all

.PHONY: all clean fclean re libmlx
