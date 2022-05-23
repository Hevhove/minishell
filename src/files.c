/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:15:05 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/05/23 10:15:48 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	open_files(t_cmd cmd)
{
	int	i;

	i = 0;
	while (i < cmd.argc)
	{
		if (cmd.scmds[i].fd_in.fname != NULL && !access(cmd.scmds[i].fd_in.fname, F_OK | R_OK))
			cmd.scmds[i].fd_in.fd = open(cmd.scmds[i].fd_in.fname, O_RDONLY);
		else if (cmd.scmds[i].fd_in.fname != NULL && access(cmd.scmds[i].fd_in.fname, F_OK | R_OK))
			printf("parse error: can't read from %s\n", cmd.scmds[i].fd_in.fname); // some exit?
		if (cmd.scmds[i].fd_out.fname != NULL && !access(cmd.scmds[i].fd_out.fname, F_OK) && access(cmd.scmds[i].fd_out.fname, W_OK))
				printf("parse error: can't write to %s\n", cmd.scmds[i].fd_out.fname);
		else if (cmd.scmds[i].fd_out.fname != NULL && cmd.scmds[i].append == 1)
			cmd.scmds[i].fd_out.fd = open(cmd.scmds[i].fd_out.fname, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else if (cmd.scmds[i].fd_out.fname != NULL && cmd.scmds[i].append == 0)
			cmd.scmds[i].fd_out.fd = open(cmd.scmds[i].fd_out.fname, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (cmd.scmds[i].fd_in.fd < 0 || cmd.scmds[i].fd_out.fd < 0)
			; // some exit?
		i++;
	}
}

void	close_files(t_cmd cmd)
{
	int	i;
	int	j;
	
	i = 0;
	while (i < cmd.argc)
	{
		j = 0;
		while (j < cmd.scmds[i].argc)
		{
			if (cmd.scmds[i].fd_in.fname != NULL)
				close(cmd.scmds[i].fd_in.fd);
			if (cmd.scmds[i].fd_out.fname != NULL)
				close(cmd.scmds[i].fd_out.fd);
			if (cmd.scmds[i].fd_err.fname != NULL)
				close(cmd.scmds[i].fd_err.fd);
			j++;
		}
		i++;
	}
}

void	set_redirections(t_cmd *cmd, int i)
{
	if (cmd->scmds[i].fd_in.fname != NULL)
		dup2(cmd->scmds[i].fd_in.fd, 0);
	if (cmd->scmds[i].fd_out.fname != NULL)
		dup2(cmd->scmds[i].fd_out.fd, 1);
}
