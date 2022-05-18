/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:33:00 by mmaxime-          #+#    #+#             */
/*   Updated: 2022/05/18 17:46:31 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	builtin_identifier(char **tokens)
{
	int		cmd_no;
	int		i;
	char	**list_of_builtin;

	cmd_no = 7;
	list_of_builtin = (char **)malloc(7 * sizeof(char *));
	list_of_builtin[0] = ft_strdup("exit");
	list_of_builtin[1] = ft_strdup("echo");
	list_of_builtin[2] = ft_strdup("cd");
	list_of_builtin[3] = ft_strdup("pwd");
	list_of_builtin[4] = ft_strdup("export");
	list_of_builtin[5] = ft_strdup("unset");
	list_of_builtin[6] = ft_strdup("env");
	list_of_builtin[7] = ft_strdup("\0");
	i = 0;
	while (i < cmd_no)
	{
		if (ft_strcmp(tokens[0], list_of_builtin[i]) == 0)
			return (i + 1);
		i++;
	}
	return (0);
}

int	builtin_executor(char **tokens, t_list **env)
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
		exec_cd(tokens, env);
	else if (builtin_id == 4)
		exec_pwd(tokens);
	else if (builtin_id == 5)
		exec_export(tokens, env);
	//else if (builtin_id == 6)
		//exec_unset(tokens);
	else if (builtin_id == 7)
		exec_env(tokens, env);
	return (1);
}
