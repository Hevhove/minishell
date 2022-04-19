# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmaxime- <mmaxime-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/14 10:25:00 by mmaxime-          #+#    #+#              #
#    Updated: 2022/04/19 17:53:26 by mmaxime-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Variables

NAME			=	minishell
CC				=	gcc
RM				=	rm -f
CFLAGS			=	-Wall -Wextra -Werror 
COMPILE_FLAGS	=	-lreadline -L${HOME}/.brew/opt/readline/lib
OBJ_FLAGS		=	-I${HOME}/.brew/opt/readline/include

#Sources

SRCS			=	$(wildcard src/*.c)
INCLUDES		=	inc/minishell.h
LIBFT			=	libft/libft.a
LIBFT_DIR		=	libft

#Binaries

OBJS			=	$(SRCS:.c=.o)

#Rules

all:		$(NAME)

$(LIBFT):
				make -C $(LIBFT_DIR) --silent

$(NAME):	$(SRCS) $(OBJS) $(LIBFT)
				$(CC) $(CFLAGS) $(COMPILE_FLAGS) -I$(INCLUDES) -o $(NAME) $(OBJS) $(LIBFT)

obj/%.o:	%.c
				$(CC) $(CFLAGS) $(OBJ_FLAGS) -c $< -o $@

debug:		$(LIBFT)
				$(CC) -g $(CFLAGS) -I$(INCLUDES) -o $(NAME) $(OBJS) $(LIBFT)

valgrind:
				valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

clean:
				$(RM) $(OBJS)
				make -C $(LIBFT_DIR) clean

fclean:		clean
				$(RM) $(NAME)
				$(RM) -R fdf.dSYM fdf_bonus.dSYM
				make -C $(LIBFT_DIR) fclean

re:			fclean all

.PHONY:		all clean fclean re debug
