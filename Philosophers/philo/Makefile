# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 12:39:42 by tdutel            #+#    #+#              #
#    Updated: 2023/03/29 14:13:47 by tdutel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
HEADER = philo.h
CC = cc
CFLAGS = -Wall -Werror -Wextra #-fsanitize=thread
SRC =	main.c			parsing.c			philo_exe.c	\
		philo_forks.c	philo_init.c	philo_routine.c	\
		philo_state.c	philo_utils.c

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
