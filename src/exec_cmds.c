/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 13:35:49 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/05/16 18:17:11 by hvan-hov         ###   ########.fr       */
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
	cmd.scmds[0].fd_in.fd = open(".heredoc_tmp", O_RDONLY);
}

void	exec_cmds(t_cmd cmd) // cat << EOF
{
	// (void)cmd;
	// STEP 1: if heredoc of first scmd is 1, then open controls for heredoc
	if (cmd.scmds[0].heredoc == 1)
		heredoc_input(cmd, cmd.scmds[0].fd_in.fname);
	// STEP 2: open files
	
	// STEP 3: open pipes

	// STEP 4: build the paths/envp to where to execute cmds
	// if no absolute path is given, execute relative path?

	// STEP 5: launch children for every pipe and execute either binaries or built-ins

	// STEP 6: close the pipes and fds, waitpid processes

	// STEP 7: free all the information used above, delete heredoc
}
