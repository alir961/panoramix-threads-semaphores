##
## EPITECH PROJECT, 2023
## panoramix
## File description:
## Makefile
##

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -pthread
SRC		=	$(wildcard src/*.c)
OBJ		=	$(SRC:.c=.o)
NAME	=	panoramix

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

tsan:
	$(CC) $(CFLAGS) -g -fsanitize=thread -o $(NAME)_tsan $(SRC)

asan:
	$(CC) $(CFLAGS) -g -fsanitize=address,undefined -o $(NAME)_asan $(SRC)

tests_run:	tsan asan
	tests/stress.sh ./$(NAME)_tsan
	tests/stress.sh ./$(NAME)_asan

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) $(NAME)_tsan $(NAME)_asan

re: fclean all

.PHONY: all tsan asan tests_run clean fclean re
