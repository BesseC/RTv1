# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbesse <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/01 12:13:48 by cbesse            #+#    #+#              #
#    Updated: 2018/03/01 12:13:50 by cbesse           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1
SRC = test.c vec1.c vec2.c mlx.c setting.c
OBJ = $(SRC:.c=.o)
CC = cc
FLAGS =
LIB = -Llibft -lft -lmlx

all : $(NAME)

$(NAME) : $(OBJ)
	@cd libft && make
	@cd minilibx_macos && make
	@$(CC) -o $(NAME) $(FLAGS) $(OBJ) $(LIB) -framework OpenGL -framework Appkit
	@echo "Compilation termine"

%.o : %.c
	@echo "\033[0;36m\033[1ACompilation de $@\033[0m"
	@$(CC) $(FLAGS) -c $<

clean :
	@rm -rf $(OBJ)
	@cd libft && make clean
	@cd minilibx_macos && make clean
	@echo "\033[1;32mSuppresion des objets ternime\033[0m"

fclean : clean
	@rm -rf $(NAME) $(LIB)
	@cd libft && make fclean
	@echo "\033[1;32mSuppresion de la librairie\033[0m"

re : fclean all
