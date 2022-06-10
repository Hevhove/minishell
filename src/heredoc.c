/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 17:17:52 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/10 16:03:25 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	open_heredoc(t_cmd cmd, int i)
{
	//printf("opening: %s\n", cmd.scmds[i].fd_in.fname);
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

	//printf("test\n");
	file = open(cmd.scmds[i].fd_in.fname, O_CREAT | O_WRONLY | O_TRUNC, 000644);
	if (file < 0)
	{
		ft_putstr_fd("error: unable to open temporary heredoc file\n", 2);
		return (-1);
	}
	//printf("i is: %d\n",i );
	//printf("delim is: %s\n", delim);
	while (1)
	{
		write(1, "> ", 2);
		//ft_putstr_fd("hello\n", 1);
		line = get_next_line(0);
		//ft_putstr_fd("hello2\n", 1);
		if (!line)
			return (0);
		//ft_putstr_fd("hello3\n", 1);
		if (!ft_strncmp(delim, line, ft_strlen(delim)))
			break ;
		//ft_putstr_fd("hello4\n", 1);
		write(file, line, ft_strlen(line));
		//printf("written line: %s\n", line);
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
				unlink(cmd.scmds[i].fd_in.fname);
			}
			j++;
		}
		i++;
	}
}
