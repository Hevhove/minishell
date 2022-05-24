/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 10:17:56 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/05/24 16:17:26 by mmaxime-         ###   ########.fr       */
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
# include <termcap.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <signal.h>
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
	int		pid;
}	t_scmd;

typedef struct s_cmd {
	int			argc;
	t_scmd		*scmds;
	char		**tokens;
	int			*pipes;
	t_list		**env;
	char		**paths;
	uint8_t		exit_status;
}	t_cmd;

// GLOBALS
t_cmd cmd;

// FUNCTION PROTOTYPES
char		**tokenize(const char *s);
void		print_tokens(char **tokens);
void		expand_tokens(char **tokens);
void		print_tokens(char **tokens);
int			check_token_type(int token);
int			check_quotes(const char *s);
int			metachar_wordlen(const char *s, int offset);
void		build_cmds(char **tokens, t_cmd *cmd);
void		exec_echo(char **tokens);
int			exec_cd(char **tokens, t_list **env);
int			exec_pwd(void);
int			exec_export(char **tokens, t_list **env);
void		exec_env(t_list **env);
int			exec_unset(char **tokens, t_list **env);
int			builtin_identifier(char *tokens);
int			builtin_executor(char **tokens, t_list **env);
void		env_init(t_list **env, char **envp);
char		*get_env_value(char *name, t_list **env);
void		export_no_var(t_list **env);
int			already_in_env(char **tokens, t_list **env);
void		free_tokens(char **tokens);
void		free_cmds(t_cmd cmd);
int			count_cmds(char **tokens);
int			skip_token(char *token);
int			scmd_arg_count(char **tokens, int index);
int			raw_arg_count(t_cmd *cmd, char **tokens, int i, int j);
void		write_raw_cmds(t_cmd *cmd, char **tokens);
void		set_cmd_count(char **tokens, t_cmd *cmd);
void		write_fds(t_cmd *cmd, char *fname, const char *mode, int pos);
void		init_scmd_fds(t_cmd *cmd, int i);
void		update_fds(t_cmd *cmd);
int			count_argv(t_scmd scmd);
void		exec_cmds(t_cmd *cmd);
void		ft_clear_env(t_list **env);
char		*get_next_line(int fd);
void		rm_env_var(t_list **env);
void		ft_free(char **ptr);
void		set_pwd_vars_env(char *old_pwd, char *new_pwd, t_list **env);
char		*find_path(t_list **env);
void		build_paths(t_cmd *cmd);
char		*get_term_var(t_list **env);
void		ft_unlink(t_cmd cmd);
char 		*get_bin(char **paths, char *bin);
void		heredoc_input(t_cmd cmd, char *delim);
void		ft_unlink(t_cmd cmd);
void		init_term(void);
int			count_list_len(t_list **env);
char		**create_envp(t_list **env);
void		create_pipes(t_cmd *cmd);
void		close_pipes(t_cmd *cmd);
void		open_files(t_cmd cmd);
void		close_files(t_cmd cmd);
void		set_redirections(t_cmd *cmd, int i);

#endif
