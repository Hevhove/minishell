/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:03:14 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/08 18:19:30 by hvan-hov         ###   ########.fr       */
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
		ft_printf("parse error: unexpected token\n");
		return (0);
	}
	if (i >= 1 && ft_strncmp(tokens[i - 1], "|", 1) == 0)
	{
		ft_printf("parse error: unexpected token\n");
		return (0);
	}
	return (1);
}

int	check_heredocs(t_cmd cmd)
{
	int	i;
	int	heredoc_count;

	i = 0;
	heredoc_count = 0;
	while (i < cmd.argc)
	{
		if (cmd.scmds[i].heredoc == 1)
			heredoc_count++;
		i++;
	}
	return (heredoc_count);
}

int	build_and_exec_cmds(t_cmd *cmd)
{
	int	ret;

	cmd->envp = create_envp(cmd->env);
	build_cmds(cmd->tokens, cmd);
	build_paths(cmd);
	ret = exec_cmds(cmd);
	if (ret < 0)
	{
		if (ret == -1)
			ft_putstr_fd("error: shell failed to open files and pipes\n", 2);
		if (ret == -2)
			ft_putstr_fd("error: shell failed to close pipes\n", 2);
		if (ret == -3)
			ft_putstr_fd("error: shell failed to close files\n", 2);
		cmd->exit_status = -1;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argv;
	(void)argc;
	line = NULL;
	ft_setup(&g_cmd, envp);
	while (1)
	{
		line = rl_gets(line);
		if (!line)
			break ;
		g_cmd.tokens = tokenize(line);
		if (!g_cmd.tokens)
			continue ;
		print_tokens(g_cmd.tokens);
		if (verify_tokens(g_cmd.tokens) && g_cmd.tokens)
		{
			build_and_exec_cmds(&g_cmd);
			free_cmds(g_cmd);
		}
		free_tokens(g_cmd.tokens);
	}
	ft_clear_env(g_cmd.env);
	return (0);
}
