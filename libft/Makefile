NAME = libft.a
CFLAGS = -Wall -Werror -Wextra
SRC =	ft_memset.c		ft_bzero.c		ft_memcpy.c		ft_memccpy.c\
		ft_memmove.c 	ft_memchr.c 	ft_memcmp.c\
		ft_strlen.c		ft_strlcpy.c 	ft_strlcat.c\
		ft_strchr.c 	ft_strrchr.c\
		ft_strnstr.c	ft_strncmp.c 	ft_atoi.c\
		ft_isalpha.c 	ft_isdigit.c 	ft_isalnum.c 	ft_isascii.c 	ft_isprint.c\
		ft_toupper.c 	ft_tolower.c 	ft_strdup.c 	ft_calloc.c\
		\
		ft_substr.c		ft_strjoin.c	ft_strtrim.c	ft_itoa.c 		ft_strmapi.c 	ft_split.c\
		ft_putchar_fd.c ft_putstr_fd.c 	ft_putendl_fd.c ft_putnbr_fd.c 	get_next_line.c

SRC_BONUS =		ft_lstadd_front.c 		ft_lstsize.c 	ft_lstlast.c 	ft_lstadd_back.c\
				ft_lstiter.c 			ft_lstmap.c     ft_lstnew.c 	ft_lstdelone.c 	ft_lstclear.c

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

.PHONY: all clean fclean re

%.o: %.c
	gcc $(CFLAGS) -c $< -o $(<:.c=.o)	

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

all: $(NAME)

clean: 
	rm -rf $(OBJ) $(OBJ_BONUS)

fclean:	clean
	rm -rf $(NAME)

bonus: $(NAME) $(OBJ) $(OBJ_BONUS)
	ar -rcs $(NAME) $(OBJ) $(OBJ_BONUS)

re: fclean $(NAME)
