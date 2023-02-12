NAME	= minishell
NAME_DEBUG = minishell.dSYM

SRCS	= $(wildcard src/*c)
OBJS	= $(SRCS:c=o)

INCS	= inc/minishell.h
LIBS	= -lreadline

CC		= gcc -g
CFLAGS	= -Wall -Wextra -Werror `pkg-config readline --cflags` #-fsanitize=address

RM		= rm -f

LIBFT	= libft/libft.a
LIBFT_DIR = libft

.PHONY: all clean fclean re debug

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -I$(INCS) -c $< -o ${<:.c=.o}

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -I$(INCS) $(LIBS) -o $(NAME) $(OBJS) $(LIBFT)
	
$(LIBFT):
	make -C $(LIBFT_DIR) --silent

debug: $(LIBFT)
	$(CC) -g $(CFLAGS) -I$(INCS) -lreadline -L $(LIBFT) $(SRCS) -o $(NAME)

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(NAME)

clean:
	$(RM) $(OBJS)
	make -s clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) -R $(NAME_DEBUG)
	make -s fclean -C $(LIBFT_DIR)

re:	fclean all
