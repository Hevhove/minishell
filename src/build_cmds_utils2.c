/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmds_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 19:26:33 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/13 16:54:09 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	set_cmd_count(char **tokens, t_cmd *cmd)
{
	int	i;
	int	j;

	cmd->argc = count_cmds(tokens);
	cmd->scmds = (t_scmd *)malloc((cmd->argc) * sizeof(t_scmd));
	if (!cmd->scmds)
		return (-1);
	i = 0;
	j = 0;
	while (tokens[i])
	{
		i += raw_arg_count(cmd, tokens, i, j);
		if (tokens[i] && ft_strncmp(tokens[i], "|", 1) == 0)
			i++;
		j++;
	}
	return (0);
}

/*
	In below function, should we still free 
	in case of echo "hello" > outfile >> outfile2?
	we might overwrite fname here which is a strdup causing memleak
*/

void	write_fds(t_cmd *cmd, char *fname, const char *mode, int pos)
{
	if (ft_strncmp(mode, ">>", 2) == 0)
	{
		cmd->scmds[pos].fd_out.fname = fname;
		cmd->scmds[pos].append = 1;
	}
	else if (ft_strncmp(mode, "<<", 2) == 0)
	{
		cmd->scmds[pos].fd_in.fname = fname;
		cmd->scmds[pos].heredoc = 1;
	}
	else if (ft_strncmp(mode, ">", 1) == 0)
	{
		cmd->scmds[pos].fd_out.fname = fname;
		cmd->scmds[pos].append = 0;
	}
	else if (ft_strncmp(mode, "<", 1) == 0)
	{
		cmd->scmds[pos].fd_in.fname = fname;
		cmd->scmds[pos].heredoc = 0;
	}
}

void	init_scmd_fds(t_cmd *cmd, int i)
{
	cmd->scmds[i].append = 0;
	cmd->scmds[i].heredoc = 0;
	cmd->scmds[i].fd_in.fname = NULL;
	cmd->scmds[i].fd_out.fname = NULL;
	cmd->scmds[i].fd_err.fname = NULL;
	cmd->scmds[i].fd_in.fd = 0;
	cmd->scmds[i].fd_out.fd = 1;
	cmd->scmds[i].fd_err.fd = 2;
}

void	update_fds(t_cmd *cmd)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cmd->argc)
	{
		j = -1;
		init_scmd_fds(cmd, i);
		while (++j < cmd->scmds[i].raw_argc)
		{
			if (cmd->scmds[i].raw[j]
				&& ft_strncmp(cmd->scmds[i].raw[j], ">>", 2) == 0)
				write_fds(cmd, cmd->scmds[i].raw[++j], ">>", i);
			else if (cmd->scmds[i].raw[j]
				&& ft_strncmp(cmd->scmds[i].raw[j], "<<", 2) == 0)
				write_fds(cmd, cmd->scmds[i].raw[++j], "<<", i);
			else if (cmd->scmds[i].raw[j]
				&& ft_strncmp(cmd->scmds[i].raw[j], ">", 1) == 0)
				write_fds(cmd, cmd->scmds[i].raw[++j], ">", i);
			else if (cmd->scmds[i].raw[j]
				&& ft_strncmp(cmd->scmds[i].raw[j], "<", 1) == 0)
				write_fds(cmd, cmd->scmds[i].raw[++j], "<", i);
		}
	}
}

int	count_argv(t_scmd scmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (scmd.raw[i])
	{
		if (check_token_type(scmd.raw[i][0]) == 1)
		{
			i += 2;
			continue ;
		}
		count++;
		i++;
	}
	return (count);
}
