/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 13:35:49 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/06 17:13:35 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	child(t_cmd *cmd, int i, char **envp)
{
	char	*bin;

	cmd->scmds[i].pid = fork();
	exec_signals(CHILD_PROCESS);
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
		if (builtin_identifier(cmd->scmds[i].argv[0]))
		{
			builtin_executor(cmd->scmds[i].argv, cmd, envp);
			free_cmds(*cmd);
			free_tokens(cmd->tokens);
			ft_clear_env(cmd->env);
			free(envp);
			exit(0);
		}
		else
		{
			bin = get_bin(cmd->paths, cmd->scmds[i].argv[0]);
			if (!bin)
			{
				ft_printf("error: command not found\n");
				free_tokens(cmd->tokens);
				free_cmds(*cmd);
				exit(127);
			}
			execve(bin, cmd->scmds[i].argv, envp);
		}
	}
}

int	exec_cmds(t_cmd *cmd)
{
	int		i;
	char	**envp;
	int		status;

	envp = create_envp(cmd->env);
	if (cmd->argc == 1 && builtin_identifier(cmd->scmds[0].argv[0]) == 2)
		cmd->exit_status = builtin_executor(cmd->scmds[0].argv, cmd, envp);
	else
	{
		if ((*cmd).scmds[0].heredoc == 1)
		{
			if (heredoc_input((*cmd), (*cmd).scmds[0].fd_in.fname) < 0)
				return (-1);
		}
		if (open_files(cmd) < 0)
			return (-1);
		if (create_pipes(cmd) < 0)
			return (-1);
		if (!cmd->paths)
			error_message("Malloc error\n", 1, cmd);
		i = -1;
		while (++i < cmd->argc)
			child(cmd, i, envp);
		if (close_pipes(cmd) < 0)
			return (-1);
		while (wait(&status) > 0)
			;
		exec_signals(RESET);
		if (WIFEXITED(status))
			cmd->exit_status = WEXITSTATUS(status);
		if (close_files(*cmd) < 0)
			return (-1);
	}
	free(envp);
	return (0);
}
