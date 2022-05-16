/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 10:17:56 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/05/16 18:06:57 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	ERROR MANAGEMENT:
	1: MALLOC ERROR
	2: OPEN ERROR
	3: 
*/

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# define METACHARSET ""

// STRUCTS

typedef enum s_token_type{
	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_AMPERSAND = '&',
	CHAR_SQUOTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_WHITESPACE = ' ',
	CHAR_NEWLINE = '\n',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_NULL = 0,
	TOKEN	= -1,
}	t_token_type;

typedef struct s_fd {
	char	*fname;
	int		fd;
}	t_fd;

typedef struct s_simp_cmd
{
	int		raw_argc;
	char	**raw;
	int		argc;
	char	**argv;
	t_fd	fd_in;
	t_fd	fd_out;
	t_fd	fd_err;
	int		heredoc;
	int		append;
}	t_scmd;

typedef struct s_cmd {
	int			argc;
	t_scmd		*scmds;
}	t_cmd;

// FUNCTION PROTOTYPES
char	**tokenize(const char *s);
void	print_tokens(char **tokens);
void	expand_tokens(char **tokens);
void	print_tokens(char **tokens);
int		check_token_type(int token);
int		check_quotes(const char *s);
int		metachar_wordlen(const char *s, int offset);
void	build_cmds(char **tokens, t_cmd *cmd);
void	exec_echo(char **tokens);
void	exec_cd(char **tokens);
void	exec_pwd(char **tokens);
void	exec_export(char **tokens, t_list **env);
void	exec_env(char **tokens, t_list **env);
int		builtin_identifier(char **tokens);
int		builtin_executor(char **tokens, t_list **env);
void	env_init(t_list **env, char **envp);
void	export_no_var(t_list **env);
int		check_in_env(t_list *new, t_list **env);
void	free_tokens(char **tokens);
void	free_cmds(t_cmd cmd);
int		count_cmds(char **tokens);
int		skip_token(char *token);
int		scmd_arg_count(char **tokens, int index);
int		raw_arg_count(t_cmd *cmd, char **tokens, int i, int j);
void	write_raw_cmds(t_cmd *cmd, char **tokens);
void	set_cmd_count(char **tokens, t_cmd *cmd);
void	write_fds(t_cmd *cmd, char *fname, const char *mode, int pos);
void	init_scmd_fds(t_cmd *cmd, int i);
void	update_fds(t_cmd *cmd);
int		count_argv(t_scmd scmd);
void	exec_cmds(t_cmd cmd);

char	*get_next_line(int fd);

#endif
