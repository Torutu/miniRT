NAME = minirt
LIBMLX := ./MLX42
HEADERS := -I $(LIBMLX)/include

LIBFT = ./inc/libft/libft.a

SRCS = main.c \
	   sphere.c \
	   vector.c \
	   raytracer.c

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
		git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX); \
	fi

# Build libft
$(LIBFT):
	@make -C ./inc/libft

# Build libmlx
libmlx: $(LIBMLX)
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

# Compile object files
%.o: %.c
	@cc -Wall -Wextra -Werror -c -g $< -o $@

# Link the final executable
$(NAME): $(OBJS) $(LIBFT)
	@cc -Wall -Wextra -Werror -g $(OBJS) $(LIBS) $(LIBFT) $(HEADERS) -o $@
	@echo "$(COLOR_GREEN)fract-ol is compiled$(COLOR_RESET)"

# Clean up object files and libmlx build directory
clean:
	@rm -f $(OBJS)
	@rm -rf $(LIBMLX)/build
	@make clean -C ./inc/libft

# Full clean including the executable
fclean: clean
	@rm -f $(NAME)
	@rm -rdf $(LIBMLX)
	@make fclean -C ./inc/libft

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re libmlx