# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbrazhni <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/05 13:39:23 by vbrazhni          #+#    #+#              #
#    Updated: 2019/07/20 17:59:18 by vbrazhni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

CC = gcc
FLAGS = -Wall -Werror -Wextra -O3
LIBRARIES = -lmlx -lm \
	-L$(MINILIBX_DIRECTORY)\
	-framework OpenGL -framework AppKit
INCLUDES = -I$(HEADERS_DIRECTORY) -I$(MINILIBX_HEADERS)

MINILIBX = $(MINILIBX_DIRECTORY)libmlx.a
MINILIBX_DIRECTORY = ./minilibX/
MINILIBX_HEADERS = $(MINILIBX_DIRECTORY)

HEADERS_LIST = fractol.h utils.h \
				bship.h julia.h mandelbrot.h

HEADERS_DIRECTORY = ./includes/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_DIRECTORY = ./sources/
SOURCES_LIST = main.c painter.c utils.c motion.c \
				mandelbrot.c julia.c bship.c \
				complex1.c complex2.c init.c hooks.c

SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

OBJECTS_DIRECTORY = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

.PHONY: all clean fclean re

all: $(NAME)

norme:
	norminette includes sources

$(NAME): $(MINILIBX) $(OBJECTS_DIRECTORY) $(OBJECTS)
	$(CC) $(FLAGS) $(LIBRARIES) $(INCLUDES) $(OBJECTS) -o $(NAME)


$(OBJECTS):
	@$(CC) -c $(FLAGS) $(INCLUDES) $(SOURCES)
	mv $(OBJECTS_LIST) $(OBJECTS_DIRECTORY)

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@

$(MINILIBX):
	@$(MAKE) -sC $(MINILIBX_DIRECTORY)

clean:
	@$(MAKE) -sC $(MINILIBX_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)

fclean: clean
	@rm -f $(MINILIBX)
	@rm -f $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all