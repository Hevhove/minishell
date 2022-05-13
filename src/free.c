/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:33:44 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/05/13 13:48:20 by hvan-hov         ###   ########.fr       */
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

// void	free_fds(t_cmd cmd)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < cmd.argc)
// 	{
// 		j = 0;
// 		while (j < 3)
// 		{
// 			if (cmd.scmds[i].fd_in.fname)
// 				free(cmd.scmds[i].fd_in.fname);
// 			if (cmd.scmds[i].fd_out.fname)
// 				free(cmd.scmds[i].fd_out.fname);
// 			if (cmd.scmds[i].fd_err.fname)
// 				free(cmd.scmds[i].fd_err.fname);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void	free_scmds(t_cmd cmd)
// {
// 	int	i;
	
// 	i = 0;
// 	while (i < cmd.argc)
// 	{
// 		free(cmd.scmds);
// 		i++;
// 	}
// }

void	free_cmds(t_cmd cmd)
{
	free_raw(cmd);
	free_argv(cmd);
	//free_fds(cmd);
	free(cmd.scmds);
	//free_scmds(cmd);
}
