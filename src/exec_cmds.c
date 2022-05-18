/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 13:35:49 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/05/17 17:58:28 by hvan-hov         ###   ########.fr       */
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
	// free(cmd.scmds[0].fd_in.fname);
	cmd.scmds[0].fd_in.fname = ft_strdup(".heredoc_tmp"); // why no free before this?
	cmd.scmds[0].fd_in.fd = open(".heredoc_tmp", O_RDONLY);
	// UNLINK LATER (SEE PIPEX)
}

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

void	create_pipes(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->argc > 1) // CHECK VALGRIND -> INVALID WRITE??
	{
		cmd->pipes = (int *)malloc((cmd->argc - 1) * sizeof(int));
		if (!cmd->pipes)
			; // some error code;
		while (i < cmd->argc - 1)
		{
			if (pipe(cmd->pipes + 2 * i) < 0)
				; // free the parent or something
			i++;
		}
	}
	return ;
}

// Write another function for close pipes..

char	*find_path(t_list **env)
{
	char	*line;

	line = NULL;
	while ((*env)->next != NULL)
	{
		if (ft_strncmp((*env)->content, "PATH", 4) == 0)
		{
			line = ft_strdup((*env)->content + 5);
			return (line);
		}
		(*env) = (*env)->next;
	}
	printf("path not found\n");
	return (line);
}

void	exec_cmds(t_cmd *cmd) // cat << EOF
{
	char	**paths;
	
	// (void)cmd;
	// STEP 1: if heredoc of first scmd is 1, then open controls for heredoc
	if ((*cmd).scmds[0].heredoc == 1)
		heredoc_input((*cmd), (*cmd).scmds[0].fd_in.fname);
	// STEP 2: open files
	open_files(*cmd);
	// STEP 3: open pipes
	create_pipes(cmd);
	// STEP 4: build the paths/envp to where to execute cmds
	// if no absolute path is given, execute relative path?
	paths = ft_split(find_path(cmd->env), ':');
	int i = 0;
	while (paths[i])
	{
		printf("paths[%d] is: %s\n", i, paths[i]);
		i++;
	}
	// STEP 5: launch children for every pipe and execute either binaries or built-ins
	
	// STEP 6: close the pipes and fds, waitpid processes
	
	// STEP 7: free all the information used above, delete heredoc
}
