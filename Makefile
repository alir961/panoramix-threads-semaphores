##
## EPITECH PROJECT, 2023
## B-CCP-400-LYN-4-1-panoramix-ali.raad
## File description:
## Makefile
##

FLAGS = -Werror -Wall -Wextra

SRC	=	$(wildcard src/*.c)

OBJ	=	$(SRC:.c=.o)

NAME	=	panoramix

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ)

clean:
	cd src && rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all
