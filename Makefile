SRCS	= $(wildcard src/*c)
NAME	= minishell
NAME_DEBUG = minishell.dSYM
INCS	= inc/minishell.h
42INCS	= /Users/$(USER)/.brew/opt/readline/include
42LINK 	= /Users/$(USER)/.brew/opt/readline/lib
HENDRIKINCS = /usr/local/Cellar/readline/include
HENDRIKLINK = /usr/local/Cellar/readline/lib
OBJS	= $(SRCS:c=o)
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror `pkg-config readline --cflags` -fsanitize=address
RM		= rm -f
LIBFT	= libft/libft.a
LIBFT_DIR = libft
USER = hvan-hov

.PHONY: all clean fclean re debug

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -I$(INCS) -c $< -o ${<:.c=.o}

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -I$(INCS) -I$(42INCS) -lreadline -L $(42LINK) -o $(NAME) $(OBJS) $(LIBFT)

hendrik: $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -I$(INCS) -I$(HENDRIKINCS) -lreadline -L $(HENDRIKLINK) -o $(NAME) $(OBJS) $(LIBFT)
	
$(LIBFT):
	make -C $(LIBFT_DIR) --silent

debug: $(LIBFT)
	$(CC) -g $(CFLAGS) -I$(INCS) $(LIBFT) $(SRCS) -o $(NAME)

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

clean:
	$(RM) $(OBJS)
	make -s clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) -R $(NAME_DEBUG)
	make -s fclean -C $(LIBFT_DIR)

re:	fclean all
