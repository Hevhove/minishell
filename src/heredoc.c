/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 17:17:52 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/07 11:14:38 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	open_heredoc(t_cmd cmd, int i)
{
	cmd.scmds[i].fd_in.fname = ft_strdup(".heredoc_tmp");
	cmd.scmds[i].fd_in.fd = open(".heredoc_tmp", O_RDONLY);
	if (cmd.scmds[i].fd_in.fd < 0)
	{
		ft_printf("error: unable to open temporary heredoc file\n");
		return (-1);
	}
	return (0);
}

int	heredoc_input(t_cmd cmd, char *delim, int i)
{
	int		file;
	char	*line;

	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 000644);
	if (file < 0)
	{
		ft_printf("error: unable to open temporary heredoc file\n");
		return (-1);
	}
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
			return (-1);
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

void	ft_unlink(t_cmd cmd)
{
	int	i;
	int	j;

	i = 0;
	while (i < cmd.argc)
	{
		j = 0;
		while (j < cmd.scmds[i].argc)
		{
			if (cmd.scmds[i].heredoc == 1)
			{
				close(cmd.scmds[i].fd_in.fd);
				unlink(".heredoc_tmp");
			}
			j++;
		}
		i++;
	}
}
