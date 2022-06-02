/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miam <miam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 13:35:49 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/02 18:11:09 by miam             ###   ########.fr       */
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
			builtin_executor(cmd->scmds[i].argv, cmd->env);
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
				error_message("error: executable not found\n", 5);
			execve(bin, cmd->scmds[i].argv, envp);
		}
	}
}

void	exec_cmds(t_cmd *cmd)
{
	int		i;
	char 	**envp;
	int		status;

	envp = create_envp(cmd->env);
	if (cmd->argc == 1 && builtin_identifier(cmd->scmds[0].argv[0]) == 2)
	{
		builtin_executor(cmd->scmds[0].argv, cmd->env);
		cmd->exit_status = 0;
	}
	else
	{
		if ((*cmd).scmds[0].heredoc == 1)
			heredoc_input((*cmd), (*cmd).scmds[0].fd_in.fname);
		open_files(*cmd);
		create_pipes(cmd);
		if (!cmd->paths)
			error_message("Malloc error\n", 1);
		i = -1;
		while (++i < cmd->argc)
			child(cmd, i, envp);
		close_pipes(cmd);
		while (wait(&status) > 0);
		exec_signals(RESET);
		if (WIFEXITED(status))
			cmd->exit_status = WEXITSTATUS(status);
		close_files(*cmd);
	}
	free(envp);
}
