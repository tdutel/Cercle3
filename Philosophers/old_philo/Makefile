# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/20 14:41:55 by tdutel            #+#    #+#              #
#    Updated: 2023/03/23 14:43:43 by tdutel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
HEADER = philo.h
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC =	main.c			parse.c			init_actions.c	\
		philosophers.c	philo_utils.c	philo_tools.c

OBJ = $(SRC:.c=.o)



all :
	make $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -pthread $(OBJ) -o $@

%.o : %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -o $@ -c $<

clean :
	rm -f $(OBJ)

fclean : 
	$(MAKE) clean
	rm -f $(NAME)

re : fclean
	make all

debug :
	$(MAKE) all CFLAGS="-Wall -Werror -Wextra -g"

rdebug : fclean
	make debug

norme :
	norminette $(SRC) $(HEADER)

.PHONY: all clean fclean re debug rdebug
