# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpokalch <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/08 21:53:21 by tpokalch          #+#    #+#              #
#    Updated: 2019/03/08 22:32:35 by tpokalch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

OBJ = main.o events.o calc_fract.o

all: $(NAME)

$(NAME):
	make -C libft/ fclean && make -C libft/
	gcc -Wall -Wextra -Werror -pthread -I libft/includes -o main.o -c main.c
	gcc -Wall -Wextra -Werror -pthread -I libft/includes -o events.o -c events.c	
	gcc -Wall -Wextra -Werror -pthread -I libft/includes -o calc_fract.o -c calc_fract.c	
	gcc -I /usr/local/include $(OBJ) -o fractol -L /usr/local/lib/ -lmlx -L ./libft -lft -framework OpenGL -framework AppKit

clean:
	make -C libft/ clean
	rm -rf $(OBJ)

fclean: clean
	make -C libft/ fclean
	rm -rf $(NAME)

re: fclean all
