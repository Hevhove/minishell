/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:33:00 by mmaxime-          #+#    #+#             */
/*   Updated: 2022/06/06 17:35:16 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	builtin_identifier(char *tokens)
{
	if (ft_strcmp(tokens, "exit") == 0)
		return (2);
	else if (ft_strcmp(tokens, "echo") == 0)
		return (1);
	else if (ft_strcmp(tokens, "cd") == 0)
		return (2);
	else if (ft_strcmp(tokens, "pwd") == 0)
		return (1);
	else if (ft_strcmp(tokens, "export") == 0)
		return (2);
	else if (ft_strcmp(tokens, "unset") == 0)
		return (2);
	else if (ft_strcmp(tokens, "env") == 0)
		return (1);
	return (0);
}

int	builtin_executor(char **tokens, t_cmd *cmd)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(tokens[0], "exit") == 0)
		ft_exit(cmd, cmd->envp);
	else if (ft_strcmp(tokens[0], "echo") == 0)
		ret = exec_echo(tokens);
	else if (ft_strcmp(tokens[0], "cd") == 0)
		ret = exec_cd(tokens, cmd->env);
	else if (ft_strcmp(tokens[0], "pwd") == 0)
		ret = exec_pwd();
	else if (ft_strcmp(tokens[0], "export") == 0)
		ret = exec_export(tokens, cmd->env);
	else if (ft_strcmp(tokens[0], "unset") == 0)
		ret = exec_unset(tokens, cmd->env);
	else if (ft_strcmp(tokens[0], "env") == 0)
	{
		if (tokens[1])
		{
			printf("env: %s: No such file or directory\n", tokens[1]);
			return (-1);
		}
		ret = exec_env(cmd->env);
	}
	return (ret);
}
