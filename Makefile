# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/24 17:18:57 by bkandemi          #+#    #+#              #
#    Updated: 2022/07/17 22:07:45 by bkandemi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

C_FILES = *.c
		

O_FILES = $(C_FILES:.c=.o)

CC = gcc

CC_DEBUG = gcc -g -fsanitize=address

CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME):
	@make -C libft/ fclean && make -C libft/
	@$(CC) $(FLAGS) -c $(C_FILES)
	@$(CC) $(FLAGS) $(O_FILES) libft/libft.a -o $(NAME)

clean:
	@rm -f $(O_FILES)
	@make -C libft/ clean
 
fclean: clean
	@rm -f $(NAME)
	@make -C libft/ clean

debug:
	@make -C libft/ fclean && make -C libft/
	@$(CC_DEBUG) $(FLAGS) -c $(C_FILES)
	@$(CC_DEBUG) $(FLAGS) $(O_FILES) libft/libft.a -o $(NAME)

re:	fclean all