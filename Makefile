NAME = fdf

USER = $(shell whoami)
OS = $(shell uname)

COMPILER = cc
CFLAGS = -g -Wall -Wextra -Werror # -fsanitize=address
MLX_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

SRC = getnextline42/get_next_line.c \
      getnextline42/get_next_line_utils.c \
      main.c \
      src/parsing.c \
	  src/parsing2.c \
      src/parsing_utils.c \
      src/render.c \
      src/isometric.c \
      src/render_utils.c \
      src/error_utils.c \
      src/hooks.c \
      src/colors.c \
	  src/rotate.c \

OBJS_DIR = objs
OBJS = $(patsubst %.c, $(OBJS_DIR)/%.o, $(SRC))


all: $(OBJS_DIR) MLX42 $(NAME)


$(NAME): $(OBJS)
	@make -C libft-42 --silent
	@make -C printf42 --silent
	@$(COMPILER) $(CFLAGS) -o $(NAME) $(OBJS) ./MLX42/build/libmlx42.a libft-42/libft.a printf42/libftprintf.a $(MLX_FLAGS)


$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(COMPILER) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)


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

.PHONY: all clean fclean re mlxclean