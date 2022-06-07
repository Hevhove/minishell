/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:15:05 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/07 12:06:18 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	open_files_loop(t_cmd *cmd, int i)
{
	if (cmd->scmds[i].fd_in.fname != NULL
		&& !access(cmd->scmds[i].fd_in.fname, F_OK | R_OK))
		cmd->scmds[i].fd_in.fd = open(cmd->scmds[i].fd_in.fname, O_RDONLY);
	else if (cmd->scmds[i].fd_in.fname != NULL
		&& access(cmd->scmds[i].fd_in.fname, F_OK | R_OK))
		return (-1);
	if (cmd->scmds[i].fd_out.fname != NULL
		&& !access(cmd->scmds[i].fd_out.fname, F_OK)
		&& access(cmd->scmds[i].fd_out.fname, W_OK))
		return (-2);
	else if (cmd->scmds[i].fd_out.fname != NULL && cmd->scmds[i].append == 1)
		cmd->scmds[i].fd_out.fd = open(cmd->scmds[i].fd_out.fname,
				O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (cmd->scmds[i].fd_out.fname != NULL && cmd->scmds[i].append == 0)
		cmd->scmds[i].fd_out.fd = open(cmd->scmds[i].fd_out.fname,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (cmd->scmds[i].fd_in.fd < 0 || cmd->scmds[i].fd_out.fd < 0)
		return (-1);
	return (0);
}

int	open_files(t_cmd *cmd)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (i < cmd->argc)
	{
		ret = open_files_loop(cmd, i);
		if (ret == -1)
			ft_printf("parse error: can't read from %s\n",
				cmd->scmds[i].fd_in.fname);
		else if (ret == -2)
			ft_printf("parse error: can't write to %s\n",
				cmd->scmds[i].fd_out.fname);
		i++;
	}
	return (ret);
}

int	close_files(t_cmd cmd)
{
	int	i;
	int	ret1;
	int	ret2;

	i = 0;
	ret1 = 0;
	ret2 = 0;
	while (i < cmd.argc)
	{
		if (cmd.scmds[i].fd_in.fname != NULL)
			ret1 = close(cmd.scmds[i].fd_in.fd);
		if (cmd.scmds[i].fd_out.fname != NULL)
			ret2 = close(cmd.scmds[i].fd_out.fd);
		if (ret1 < 0)
			ft_printf("error: can't close fd_in: %s\n",
				cmd.scmds[i].fd_in.fname);
		else if (ret2 < 0)
			ft_printf("error: can't close fd_out: %s\n",
				cmd.scmds[i].fd_out.fname);
		if (ret1 < 0 || ret2 < 0)
			return (-1);
		i++;
	}
	return (0);
}

int	set_redirections(t_cmd *cmd, int i)
{
	if (cmd->scmds[i].fd_in.fname != NULL)
	{
		if (dup2(cmd->scmds[i].fd_in.fd, 0) < 0)
		{
			ft_putstr_fd("file error: unable to duplicate fd_in\n", 2);
			return (-1);
		}
	}
	if (cmd->scmds[i].fd_out.fname != NULL)
	{
		if (dup2(cmd->scmds[i].fd_out.fd, 1) < 0)
		{
			ft_putstr_fd("file error: unable to duplicate fd_out\n", 2);
			return (-1);
		}
	}
	return (0);
}
