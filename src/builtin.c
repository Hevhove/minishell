/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miam <miam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:33:00 by mmaxime-          #+#    #+#             */
/*   Updated: 2022/06/01 16:16:18 by miam             ###   ########.fr       */
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

int	builtin_executor(char **tokens, t_list **env)
{
	if (ft_strcmp(tokens[0], "exit") == 0)
	{
		printf("exit\n");
		exit (0);
	}
	else if (ft_strcmp(tokens[0], "echo") == 0)
		exec_echo(tokens);
	else if (ft_strcmp(tokens[0], "cd") == 0)
		exec_cd(tokens, env);
	else if (ft_strcmp(tokens[0], "pwd") == 0)
		exec_pwd();
	else if (ft_strcmp(tokens[0], "export") == 0)
		exec_export(tokens, env);
	else if (ft_strcmp(tokens[0], "unset") == 0)
		exec_unset(tokens, env);
	else if (ft_strcmp(tokens[0], "env") == 0)
	{
		if (tokens[1])
		{
			printf("env: %s: No such file or directory\n", tokens[1]);
			return (0);
		}
		exec_env(env);
	}
	return (1);
}
