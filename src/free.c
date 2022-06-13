/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:33:44 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/13 12:25:09 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens[i]);
	free(tokens);
}

void	free_raw(t_cmd cmd)
{
	int	i;
	int	j;

	i = 0;
	while (i < cmd.argc)
	{
		j = 0;
		while (j < cmd.scmds[i].raw_argc)
		{
			free(cmd.scmds[i].raw[j]);
			j++;
		}
		free(cmd.scmds[i].raw[j]);
		free(cmd.scmds[i].raw);
		i++;
	}
}

void	free_argv(t_cmd cmd)
{
	int	i;
	int	j;

	i = 0;
	while (i < cmd.argc)
	{
		j = 0;
		while (j < cmd.scmds[i].argc)
		{
			free(cmd.scmds[i].argv[j]);
			j++;
		}
		free(cmd.scmds[i].argv[j]);
		free(cmd.scmds[i].argv);
		i++;
	}
}

void	free_heredocs(t_cmd cmd)
{
	int	i;

	i = 0;
	while (i < cmd.argc)
	{
		if (cmd.scmds[i].heredoc == 1)
		{
			if (cmd.scmds[i].fd_in.fname)
				free(cmd.scmds[i].fd_in.fname);
			if (cmd.scmds[i].delim)
				free(cmd.scmds[i].delim);
		}
		i++;
	}
	return ;
}

void	free_cmds(t_cmd cmd)
{
	if (ft_unlink(cmd) < 0)
		ft_printf("didn't manage to unlink\n");
	free_raw(cmd);
	free_argv(cmd);
	if (cmd.paths && cmd.scmds[0].argc > 0)
		free_split(cmd.paths);
	free_heredocs(cmd);
	free(cmd.scmds);
	if (cmd.argc > 1)
		free(cmd.pipes);
	cmd.argc = 0;
}
