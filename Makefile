NAME = fdf

USER = $(shell whoami)
OS = $(shell uname)

SRCS =	

COMPILER = cc
OBJS_DIR = objs/

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
MLX_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

# Default target: ensures submodule is updated and the project is built
all: submodule_update $(NAME)

$(NAME): $(OBJS)
	@make -C libft --silent
	@make -C ft_printf --silent
	@$(COMPILER) $(CFLAGS) -o $(NAME) $(OBJS) ./MLX42/build/libmlx42.a libft/libft.a ft_printf/libftprintf.a $(MLX_FLAGS)

# Submodule update: initialize and update MLX42 submodule
submodule_update:
	@if [ ! -d "MLX42" ]; then \
		git submodule update --init --recursive; \
	fi
	@cd MLX42 && git checkout MLX42 && cmake -B build -DDEBUG=1 && cmake --build build -j4

clean:
	@rm -f $(OBJS)
	@cd ft_printf && make fclean && cd ..
	@cd libft && make fclean && cd ..

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re submodule_update