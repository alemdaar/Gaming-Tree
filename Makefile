NAME    = program
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -O2
SRC     = main.c design.c ai.c
OBJ     = $(SRC:.c=.o)
RM      = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c library.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
