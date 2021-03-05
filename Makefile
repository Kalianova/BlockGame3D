NAME = cub3d
CFLAGS = 
LXFLAGS = -lmlx -framework OpenGL -framework AppKit
LINUX = -lXext -lX11 -lm -lbsd -Lmlx_linux/ -lmlx
LINUX_MLX = mlx_linux
MLX = minilibx_opengl
SRC = main.c basic_draw.c parser.c key_hook.c
CC = gcc
OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re

%.o: %.c
	$(CC) -Imlx_linux -Ilibft -O3 -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) -L $(MLX) $(LXFLAGS) $(OBJ)

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