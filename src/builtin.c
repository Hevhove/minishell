/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miam <miam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:33:00 by mmaxime-          #+#    #+#             */
/*   Updated: 2022/05/04 16:52:04 by miam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	builtin_identifier(char **tokens)
{
	int		cmd_no;
	int		i;

	cmd_no = 7;
	char	*List_of_builtin[cmd_no];
	List_of_builtin[0] = "exit";
	List_of_builtin[1] = "echo";
	List_of_builtin[2] = "cd";
	List_of_builtin[3] = "pwd";
	List_of_builtin[4] = "export";
	List_of_builtin[5] = "unset";
	List_of_builtin[6] = "env";
	i = 0;
	while (i < cmd_no)
	{
		if (ft_strcmp(tokens[0], List_of_builtin[i]) == 0)
			return (i + 1);
		i++;
	}
	return (0);
}

int	builtin_executor(char **tokens)
{
	int	builtin_id;

	builtin_id = builtin_identifier(tokens);
	if (builtin_id == 0)
		return (0);
	else if (builtin_id == 1)
	{
		printf("exit");
		return (0);
	}
	else if (builtin_id == 2)
		exec_echo(tokens);
	else if (builtin_id == 3)
		exec_cd(tokens);
	else if (builtin_id == 4)
		exec_pwd(tokens);
	else if (builtin_id == 5)
		exec_export(tokens);
	else if (builtin_id == 6)
		exec_unset(tokens);
	else if (builtin_id == 7)
		exec_env(tokens);
	return (1);
}