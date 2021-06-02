NAME=fractol

CC=gcc

CFLAGS=-Wall -Wextra -Werror -framework OpenGL -framework AppKit minilibX/libmlx.a

RM=rm -f

LDFLAGS=-L.

LDLIBS=-lmlx -framework OpenGL -framework AppKit

SRC=main.c mandelbrot.c

OBJ=$(SRC:.c=.o)


$(NAME):
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(CFLAGS) -c $(OBJ)

all:
	gcc -g -fsanitize=address -lmlx -framework OpenGL -framework AppKit $(SRC)
easy:
	gcc -g -fsanitize=address -lmlx -framework OpenGL -framework AppKit $(SRC)
e:
	gcc -lmlx -framework OpenGL -framework AppKit $(SRC)

clean:
	$(RM) $(COBJ) $(SOBJ)

fclean: clean
	$(RM) -rf $(SERVER) $(SERVER).dSYM
	$(RM) -rf $(CLIENT) $(CLIENT).dSYM

re: fclean all

.PHONY: clean fclean all bonus