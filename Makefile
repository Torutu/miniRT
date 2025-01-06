# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: walnaimi <walnaimi@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/29 17:03:00 by sataskin          #+#    #+#              #
#    Updated: 2025/01/06 16:08:54 by walnaimi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minirt
LIBMLX := ./MLX42
HEADERS := -I $(LIBMLX)/include

LIBFT = ./libft/libft.a

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
		execute/cylinder_hit.c \
		execute/cylinder.c \
		execute/cylinder1.c \
		execute/execution.c \
		execute/init_lens.c \
		execute/hooks.c \
		execute/plane.c \
		execute/ray.c \
		execute/shadow_legend.c \
		execute/sphere.c \
		execute/utils.c \
		execute/vectooor.c \
		execute/vectooor1.c \
		main.c

OBJS = $(SRCS:.c=.o)

LIBS := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm -L "/Users/$(USER)/.brew/opt/glfw/lib/"

# ANSI color codes
COLOR_GREEN := \033[0;32m
COLOR_RESET := \033[0m

# Default target
all: libmlx $(LIBFT) $(NAME)

# Download MLX42 if not already present
$(LIBMLX):
	@if [ ! -d "$(LIBMLX)" ]; then \
		echo "$(COLOR_GREEN)Cloning MLX42 repository...$(COLOR_RESET)"; \
		git clone git@github.com:codam-coding-college/MLX42.git $(LIBMLX); \
	fi

# Build libft
$(LIBFT):
	@make -C ./libft

# Build libmlx
libmlx: $(LIBMLX)
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

# Compile object files
%.o: %.c
	@cc -Wall -Wextra -Werror -c -g $< -o $@

# Link the final executable
$(NAME): $(OBJS) $(LIBFT)
	@cc -Wall -Wextra -Werror -g $(OBJS) $(LIBS) $(LIBFT) $(HEADERS) -o $@
	@echo "$(COLOR_GREEN)minirt is compiled$(COLOR_RESET)"

# Clean up object files and libmlx build directory
clean:
	@rm -f $(OBJS)
	@rm -rf $(LIBMLX)/build
	@make clean -C ./libft

# Full clean including the executable
fclean: clean
	@rm -f $(NAME)
	@rm -rdf $(LIBMLX)
	@make fclean -C ./libft

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re libmlx