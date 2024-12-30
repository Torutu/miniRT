# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toru <toru@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/29 17:03:00 by sataskin          #+#    #+#              #
#    Updated: 2024/12/30 22:25:01 by toru             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

LIBFTPATH = ./libft

LIBFT = $(LIBFTPATH)/libft.a

# LIBMLX    := ./MLX42

#HEADERS    := -I $(LIBMLX)/include

SRCS = add_ambient.c \
		add_camera.c \
		add_cylinder.c \
		add_height.c \
		add_light.c \
		add_plane.c \
		add_sphere.c \
		colors.c \
		content_val.c \
		coordinates.c \
		diameter.c \
		file_val.c \
		free_parser.c \
		horizontal_field.c \
		lighting_ratio.c \
		make_list.c \
		orientation_vector.c \
		parsing_functions.c \
		val_num.c \
		main.c

OBJS= $(SRCS:.c=.o)

# LIBS := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm -L "/Users/$(USER)/.brew/opt/glfw/lib/"

#all: libmlx $(NAME)
all: $(NAME)

#libmlx:
#	@if [ ! -d $(LIBMLX)/build ]; then\
		cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4;\
	fi

$(OBJS): $(SRCS)
	cc -Wall -Wextra -Werror -c -g $(@:.o=.c) -o $@

$(LIBFT):
	make -C $(LIBFTPATH)

$(NAME): $(LIBFT) $(OBJS)
	cc -Wall -Wextra -Werror $(SRCS) $(LIBFT) -o $@
# cc -Wall -Wextra -Werror $(SRCS) $(LIBS) $(HEADERS) $(LIBFT) -o $@

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFTPATH)
# @rm -rf $(LIBMLX)/build

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFTPATH)

re: fclean $(NAME)

.PHONY: all, clean, fclean, re