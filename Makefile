NAME = fdf

USER = $(shell whoami)
OS = $(shell uname)

SRCS = getnextline42/get_next_line.c \
       getnextline42/get_next_line_utils.c \
       main.c \
       src/parsing.c \
       src/utils.c \
	   src/render.c \
	   src/error_utils.c \
	   src/hooks.c 		\


COMPILER = cc
OBJS_DIR = objs/

OBJS = $(SRCS:.c=.o)

CFLAGS =  -g -fsanitize=address #-Wall -Wextra -Werror
MLX_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

all: MLX42 $(NAME)

$(NAME): $(OBJS)
	@make -C libft-42 --silent
	@make -C printf42 --silent
	@$(COMPILER) $(CFLAGS) -o $(NAME) $(OBJS) ./MLX42/build/libmlx42.a libft-42/libft.a printf42/libftprintf.a $(MLX_FLAGS)

MLX42:
	@if [ ! -d "MLX42" ]; then git clone https://github.com/codam-coding-college/MLX42.git; fi
	@cd MLX42 && cmake -B build -DDEBUG=1 && cmake --build build -j4

clean:
	@rm -f $(OBJS)
	@cd printf42 && make fclean && cd ..
	@cd libft-42 && make fclean && cd ..

fclean: clean
	@rm -rf MLX42
	@rm -f $(NAME)

mlxclean:
	@rm -rf MLX42

re: fclean all

.PHONY: all clean fclean re