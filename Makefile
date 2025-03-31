NAME = fdf

USER = $(shell whoami)
OS = $(shell uname)

SRCS = getnextline42/get_next_line.c \
       getnextline42/get_next_line_utils.c \
       main.c \
       src/reading.c \
       src/drawing.c \
       src/init.c \
       src/parsing.c \
       src/utils.c

OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(notdir $(SRCS:.c=.o)))

COMPILER = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
MLX_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit -Iinclude -lglfw -L/usr/local/lib

all: MLX42 $(NAME)

$(NAME): $(OBJS)
    @make -C libft-42 --silent
    @make -C printf42 --silent
    $(COMPILER) $(CFLAGS) -o $(NAME) $(OBJS) ./MLX42/build/libmlx42.a libft-42/libft.a printf42/libftprintf.a $(MLX_FLAGS)

$(OBJS_DIR)%.o: %.c
    @mkdir -p $(OBJS_DIR)
    $(COMPILER) $(CFLAGS) -c $< -o $@

MLX42:
    @if [ ! -d "MLX42" ]; then git clone https://github.com/codam-coding-college/MLX42.git; fi
    @cd MLX42 && cmake -B build -DDEBUG=1 && cmake --build build -j4

clean:
    @rm -rf $(OBJS_DIR)
    @cd printf42 && make fclean && cd ..
    @cd libft-42 && make fclean && cd ..

fclean: clean
    @rm -rf MLX42
    @rm -f $(NAME)

mlxclean:
    @rm -rf MLX42

re: fclean all

.PHONY: all clean fclean re