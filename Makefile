NAME = cub3d
CFLAGS = 
LXFLAGS = -lmlx -framework OpenGL -framework AppKit
LINUX = -lXext -lX11 -lm -lbsd -Lmlx_linux/ -lmlx
LINUX_MLX = mlx_linux
MLX = minilibx_opengl
SRC = main.c basic_draw.c parser.c parser_map.c parser_one.c parser_add.c key_hook.c sprites.c
CC = gcc
OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re

WASINOC = -Imlx_linux -O3

%.o: %.c
	$(CC) -Iminilibx_opengl -Ilibft  -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) bonus -C libft
	gcc -o $(NAME) -L $(MLX) $(LXFLAGS) $(OBJ) -Llibft/ -lft

l: $(OBJ)
	$(MAKE) bonus -C libft
	$(CC) -o $(NAME) $(OBJ) -Lmlx_linux/ -lmlx -lXext -lX11 -lm -lbsd -L/usr/include/mlx_linux/lib -Llibft/ -lft
clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

rel: fclean l

bonus: