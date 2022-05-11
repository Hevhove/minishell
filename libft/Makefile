# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miam <miam@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/29 10:33:15 by hvan-hov          #+#    #+#              #
#    Updated: 2022/05/03 10:31:41 by miam             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	$(wildcard *.c)
INCS	= ./libft.h
OBJS	= $(SRCS:c=o)
NAME	= libft.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f

.PHONY: all bonus clean fclean re

all:	$(NAME)

.c.o: 
	$(CC) $(CFLAGS) -I$(INCS) -c $< -o ${<:.c=.o}

$(NAME):	$(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re:	fclean all
