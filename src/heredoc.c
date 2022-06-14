/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 17:17:52 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/14 15:20:48 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	open_heredoc(t_cmd cmd, int i)
{
	cmd.scmds[i].fd_in.fd = open(cmd.scmds[i].fd_in.fname, O_RDONLY);
	if (cmd.scmds[i].fd_in.fd < 0)
	{
		ft_putstr_fd("error: unable to open temporary heredoc file\n", 2);
		return (-1);
	}
	return (0);
}

int	heredoc_input(t_cmd cmd, char *delim, int i)
{
	int		file;
	char	*line;

	file = open(cmd.scmds[i].fd_in.fname, O_CREAT | O_WRONLY | O_TRUNC, 000644);
	if (file < 0)
	{
		ft_putstr_fd("error: unable to open temporary heredoc file\n", 2);
		return (-1);
	}
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
			break ;
		if (!ft_strncmp(delim, line, ft_strlen(delim)))
			break ;
		write(file, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(file);
	if (open_heredoc(cmd, i) < 0)
		return (-1);
	return (0);
}

int	ft_unlink(t_cmd cmd)
{
	int	i;

	i = 0;
	while (i < cmd.argc)
	{
		if (cmd.scmds[i].heredoc == 1)
		{
			if (close(cmd.scmds[i].fd_in.fd) < 0)
				return (-1);
			unlink(cmd.scmds[i].fd_in.fname);
		}
		i++;
	}
	return (0);
}

void	move_delims(t_scmd *scmd, int i)
{
	char	*tmp;

	scmd->delim = ft_strdup(scmd->fd_in.fname);
	scmd->fd_in.fname = NULL;
	tmp = ft_strdup(".heredoc_tmp");
	scmd->fd_in.fname = ft_strjoin(tmp, ft_itoa(i));
	free(tmp);
}
