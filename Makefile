NAME = pipex

SRC =	pipex.c pipex_utils.c
		
OBJECT = $(SRC:.c=.o)

INCLUDES = libft/libft.a

all : $(NAME)

$(NAME): $(SRC)
	cd libft && $(MAKE)
	cc  $(SRC) $(INCLUDES) -o $(NAME)

clean:
	cd libft && rm -rf *.o
	rm -rf $(OBJECT)

fclean: clean
	rm -rf $(NAME)
	cd libft && rm -rf libft.a

re: fclean all

.PHONY: all clean fclean re