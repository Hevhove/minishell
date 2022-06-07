/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 13:35:49 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/07 20:56:03 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	child_setup(t_cmd *cmd, int i)
{
	if (cmd->argc > 1)
	{
		if (i == 0)
		{
			if (dup2(cmd->pipes[1], 1) < 0)
				return (-1);
		}
		else if (i == cmd->argc - 1)
		{
			if (dup2(cmd->pipes[2 * i - 2], 0) < 0)
				return (-1);
		}
		else
		{
			if (dup2(cmd->pipes[2 * i - 2], 0) < 0)
				return (-1);
			if (dup2(cmd->pipes[2 * i + 1], 1) < 0)
				return (-1);
		}
	}
	if (close_pipes(cmd) < 0)
		return (-1);
	if (set_redirections(cmd, i) < 0)
		return (-1);
	return (0);
}

int	child_builtin_exec(t_cmd *cmd, int i)
{
	cmd->exit_status = builtin_executor(cmd->scmds[i].argv, cmd);
	free_cmds(*cmd);
	free_tokens(cmd->tokens);
	ft_clear_env(cmd->env);
	free(cmd->envp);
	exit(cmd->exit_status);
}

void	child(t_cmd *cmd, int i)
{
	char	*bin;

	cmd->scmds[i].pid = fork();
	exec_signals(CHILD_PROCESS);
	if (cmd->scmds[i].pid == 0)
	{
		child_setup(cmd, i);
		if (builtin_identifier(cmd->scmds[i].argv[0]))
			child_builtin_exec(cmd, i);
		else
		{
			bin = get_bin(cmd->paths, cmd->scmds[i].argv[0]);
			if (!bin)
			{
				ft_putstr_fd("error: command not found\n", 2);
				free_tokens(cmd->tokens);
				free_cmds(*cmd);
				exit(127);
			}
			execve(bin, cmd->scmds[i].argv, cmd->envp);
		}
	}
}

int	cmd_setup(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->argc)
	{
		if ((*cmd).scmds[i].heredoc == 1)
		{
			if (heredoc_input((*cmd), (*cmd).scmds[i].fd_in.fname, i) < 0)
				return (-1);
		}
		i++;
	}
	if (open_files(cmd) < 0)
		return (-1);
	if (create_pipes(cmd) < 0)
		return (-1);
	return (0);
}

int	exec_cmds(t_cmd *cmd)
{
	int		i;
	int		status;

	if (cmd->argc == 1 && builtin_identifier(cmd->scmds[0].argv[0]) == 2)
		cmd->exit_status = builtin_executor(cmd->scmds[0].argv, cmd);
	else
	{
		build_paths(cmd);
		if (cmd_setup(cmd) < 0)
			return (-1);
		i = -1;
		while (++i < cmd->argc)
			child(cmd, i);
		if (close_pipes(cmd) < 0)
			return (-2);
		while (wait(&status) > 0)
			;
		exec_signals(RESET);
		if (WIFEXITED(status))
			cmd->exit_status = WEXITSTATUS(status);
		if (close_files(*cmd) < 0)
			return (-3);
	}
	free(cmd->envp);
	return (0);
}
