NAME = pipex

NAME_BONUS = pipex_bonus

SRC =	pipex.c pipex_utils.c

SRC_BONUS =	pipex_bonus.c pipex_utils_bonus.c pipex_utils2_bonus.c 

OBJECT = $(SRC:.c=.o)

OBJECT_BONUS = $(SRC_BONUS:.c=.o)

INCLUDES = libft/libft.a

all : $(NAME)

$(NAME): $(SRC)
	cd libft && $(MAKE)
	cc -Wall -Wextra -Werror $(SRC) $(INCLUDES) -o $(NAME)

bonus : $(NAME_BONUS)

$(NAME_BONUS) : $(SRC_BONUS)
	cd libft && $(MAKE)
	cc -Wall -Wextra -Werror $(SRC_BONUS) $(INCLUDES) -o $(NAME_BONUS)

clean:
	cd libft && rm -rf *.o
	rm -rf $(OBJECT)
	rm -rf $(OBJECT_BONUS)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(NAME_BONUS)
	cd libft && rm -rf libft.a

re: fclean all

.PHONY: all clean fclean re bonus