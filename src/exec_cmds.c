/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 13:35:49 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/05/22 15:40:50 by hvan-hov         ###   ########.fr       */
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
	//free(cmd.scmds[0].fd_in.fname);
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
	int pipe_num;

	pipe_num = 2 * (cmd->argc - 1);
	i = 0;
	if (pipe_num > 0) // CHECK VALGRIND -> INVALID WRITE??
	{
		cmd->pipes = (int *)malloc((pipe_num) * sizeof(int));
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

// Write another function for close pipes.

char	*find_path(t_list **env)
{
	char	*line;
	t_list	*tmp;

	tmp = *env;
	line = NULL;
	while (tmp->next != NULL)
	{
		if (ft_strncmp(tmp->content, "PATH", 4) == 0)
		{
			line = ft_strdup(tmp->content + 5);
			return (line);
		}
		tmp = tmp->next;
	}
	printf("path not found\n");
	return (line);
}

char *get_bin(char **paths, char *bin)
{
	int		i;
	char	*inter;
	char	*cmd_path;

	i = 0;
	while (paths[i])
	{
		inter = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(inter, bin);
		free(inter);
		//printf("cmd_path tried is: %s\n", cmd_path);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

int	count_list_len(t_list **env)
{
	int		count;
	t_list	*tmp;

	count = 0;
	tmp = *env;
	while (tmp != NULL)
	{
		count++;
		tmp = tmp->next;
	}
	//printf("count is %d\n", count);
	return (count);
}

char	**create_envp(t_list **env)
{
	t_list 	*tmp;
	char	**envp;
	int		count;
	int		i;

	tmp = *env;
	count = count_list_len(env);
	envp = (char **)malloc((count + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	while (i < count)
	{
		envp[i] = tmp->content;
		//printf("envp[%d] is now: %s\n", i, envp[i]);
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	close_pipes(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < ( 2 * (cmd->argc - 1)))
	{
		close(cmd->pipes[i]);
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

void	child(t_cmd *cmd, int i, char **envp)
{
	char	*bin;

	cmd->scmds[i].pid = fork();
	if (cmd->scmds[i].pid == 0)
	{
		if (cmd->argc > 1)
		{
			if (i == 0)
				dup2(cmd->pipes[1], 1);
			else if (i == cmd->argc - 1)
				dup2(cmd->pipes[2 * i - 2], 0);
			else
			{
				dup2(cmd->pipes[2 * i - 2], 0);
				dup2(cmd->pipes[2 * i + 1], 1);
			}
		}
		close_pipes(cmd);
		set_redirections(cmd, i);
		bin = get_bin(cmd->paths, cmd->scmds[i].argv[0]);
		if (!bin)
		{
			printf("error bin\n");
			exit(5); // check error codes
		}
		execve(bin, cmd->scmds[i].argv, envp);
	}
}

void	exec_cmds(t_cmd *cmd) // cat << EOF
{
	int		i;
	char 	**envp;

	if ((*cmd).scmds[0].heredoc == 1)
		heredoc_input((*cmd), (*cmd).scmds[0].fd_in.fname);
	open_files(*cmd);
	create_pipes(cmd);
	if (!cmd->paths)
		; // some error code
	envp = create_envp(cmd->env);
	// STEP 4: build the paths/envp to where to execute cmds
	// if no absolute path is given, execute relative path?
	// STEP 5: launch children for every pipe and execute either binaries or built-ins
	i = -1;
	while (++i < cmd->argc)
		child(cmd, i, envp);
	close_pipes(cmd);
	while (wait(NULL) > 0);
	// STEP 6: close remaining fds
	// STEP 7: free all the information used above, delete heredoc (unlink)
}
