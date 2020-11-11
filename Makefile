NAME = cub3d
CFLAGS = -Wall -Werror -Wextra
LXFLAGS = -lmlx -framework OpenGL -framework AppKit
MLX = minilibx_opengl
SRC = main.c
OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re

%.o: %.c
	gcc $(CFLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) -L $(MLX) $(LXFLAGS) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

bonus: