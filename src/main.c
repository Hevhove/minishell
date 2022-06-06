/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:03:14 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/06 16:28:06 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
	-> We can use 1 global variable. This should probably be the error code
*/

char	*rl_gets(char *line)
{
	if (line)
	{
		free(line);
		line = NULL;
	}
	line = readline("hm-0.1$ ");
	if (line && *line)
		add_history(line);
	return (line);
}

int	verify_tokens(char	**tokens)
{
	int	i;

	i = 0;
	if (tokens[i] == NULL)
		return (0);
	while (tokens[i])
		i++;
	if (ft_strncmp(tokens[0], "|", 1) == 0)
	{
		printf("parse error: unexpected token\n");
		return (0);
	}
	if (i >= 1 && ft_strncmp(tokens[i - 1], "|", 1) == 0)
	{
		printf("parse error: unexpected token\n");
		return (0);
	}
	return (1);
}

int	check_heredocs(t_cmd cmd)
{
	int	i;
	int	j;
	int	heredoc_count;

	i = 0;
	heredoc_count = 0;
	while (i < cmd.argc)
	{
		j = 0;
		while (j < cmd.scmds[i].argc)
		{
			if (cmd.scmds[i].heredoc == 1)
				heredoc_count++;
			j++;
		}
		i++;
	}
	return (heredoc_count);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;

	(void)argv;
	(void)argc;
	init_term();
	cmd.env = (t_list **)malloc(sizeof(t_list));
	if (!cmd.env)
		return (1);
	*(cmd.env) = NULL;
	cmd.tokens = NULL;
	env_init(&cmd, envp);
	cmd.exit_status = 0;
	exec_signals(INIT);
	line = NULL;
	while (1)
	{
		line = rl_gets(line);
		if (!line)
			break ;
		cmd.tokens = tokenize(line);
		if (verify_tokens(cmd.tokens) && cmd.tokens)
		{
			expand_tokens(cmd.tokens, cmd.env);
			build_cmds(cmd.tokens, &cmd);
			build_paths(&cmd);
			if (check_heredocs(cmd) <= 1)
			{
				if (exec_cmds(&cmd) < 0)
					cmd.exit_status = -1;
			}
			else
				ft_printf("parse error\n");
			free_cmds(cmd);
		}
		free_tokens(cmd.tokens);
	}
	ft_clear_env(cmd.env);
	return (0);
}
