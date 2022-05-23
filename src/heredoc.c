/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 17:17:52 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/05/23 10:16:28 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	heredoc_input(t_cmd cmd, char *delim)
{
	int		file;
	char	*line;

	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 000644);
	if (file < 0)
		exit(2); // add error message
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
			exit(1); // exit code?
		if (!ft_strncmp(delim, line, ft_strlen(delim)))
			break ;
		write(file, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(file);
	cmd.scmds[0].fd_in.fname = ft_strdup(".heredoc_tmp");
	cmd.scmds[0].fd_in.fd = open(".heredoc_tmp", O_RDONLY);
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
				close(cmd.scmds[0].fd_in.fd);
				unlink(".heredoc_tmp");
			}
			j++;
		}
		i++;
	}
}
