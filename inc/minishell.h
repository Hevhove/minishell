/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 10:17:56 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/04/30 17:10:40 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"

// STRUCTS
typedef struct	s_ast {
	struct s_ast *left;
	struct s_ast *right;
	void *content;
}	t_ast;

typedef enum RedirType 
{
	LEFT_SINGLE, 
	LEFT_DOUBLE, 
	RIGHT_SINGLE, 
	RIGHT_DOUBLE
}	t_redir_type;

typedef enum TokenType{
	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_AMPERSAND = '&',
	CHAR_QUOTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_SEMICOLON = ';',
	CHAR_WHITESPACE = ' ',
	CHAR_ESCAPESEQUENCE = '\\',
	CHAR_TAB = '\t',
	CHAR_NEWLINE = '\n',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_NULL = 0,
	TOKEN	= -1,
}	t_token_type;

typedef struct	s_token {
	struct s_token	*prev;
	struct s_token	*next;
	enum TokenType	type;
	char			*str;
}	t_token;

typedef struct s_redir {
	t_redir_type redir_type;
	
}	t_redir;

typedef struct s_simp_cmd
{
	int		argc;
	char	**argv;
	int		fd_in;
	int		fd_out;
	int		fd_err;
}	t_simp_cmd;

typedef struct s_cmd {
	t_simp_cmd	*simple_cmd;	// ls -al
	int			fd_in;
	int			fd_out;
	int			fd_err;
}	t_cmd;

// FUNCTION PROTOTYPES
char	**tokenize(const char *s);
void	print_tokens(char **tokens);
void	expand_tokens(char **tokens);

#endif
