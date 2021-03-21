NAME = cub3d
CFLAGS = -Wall -Werror -Wextra
LXFLAGS = -lmlx -framework OpenGL -framework AppKit
LINUX = -Lmlx_linux/ -lmlx -lXext -lX11 -lm -lbsd -L/usr/include/mlx_linux/lib
LINUX_MLX = -Imlx_linux
MLX = minilibx_opengl
SRC = main.c basic_draw.c parser.c parser_map.c parser_one.c parser_add.c key_hook.c sprites.c save_bmp.c
CC = gcc
OBJ = $(SRC:.c=.o)
MLX_MAC = -Iminilibx_opengl

.PHONY: all clean fclean re

WASINOC = -Imlx_linux -O3

%.o: %.c
	$(CC) $(CFLAGS) $(MLX_MAC) -Ilibft  -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) bonus -C libft
	$(MAKE) -C minilibx_opengl
	cp minilibx_opengl/libmlx.dylib libmlx.dylib 
	$(CC) -o $(NAME) -L $(MLX) $(LXFLAGS) $(OBJ) -Llibft/ -lft

clean:
	$(MAKE) clean -C libft
	rm -rf $(OBJ)

fclean: clean
	$(MAKE) fclean -C libft
	rm -rf $(NAME)

re: fclean all

l: $(OBJ)
	$(MAKE) -C $(LINUX_MLX)
	$(MAKE) bonus -C libft
	$(CC) -o $(NAME) $(OBJ) $(LINUX) -Llibft/ -lft

rel: fclean l

bonus: $(NAME)