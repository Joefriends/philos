# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlopes-c <jlopes-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/13 12:53:58 by jlopes-c          #+#    #+#              #
#    Updated: 2025/10/02 11:12:01 by jlopes-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
ARCHIVE = philo.a
CC = cc
CFLAGS = -Wall -Werror -Wextra 
MAKE_LIB = ar -rcs

SRCS = check_valid_and_free.c get_time.c init.c philo.c create_and_print.c end_simulation.c
		
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(ARCHIVE)
	$(CC) $(ARCHIVE) -o $@

$(ARCHIVE) : $(OBJS)
	$(MAKE_LIB) $(ARCHIVE) $^

%.o : %.c 
	$(CC) $(CFLAGS) -c $< -o $@ 

clean :
	rm -f $(OBJS) $(ARCHIVE)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
