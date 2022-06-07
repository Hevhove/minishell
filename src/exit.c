/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:50:13 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/07 18:34:08 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_isnumber(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > '0' && str[i] < '9')
			i++;
		else
			return (0);
	}
	return (1);
}

void	ft_exit(t_cmd *cmd, char **envp)
{
	char *exit_code;
	int	exit_nbr;
	
	exit_code = cmd->scmds[0].argv[1];
	if (exit_code && ft_isnumber(exit_code))
	{
		exit_nbr = ft_atoi(exit_code);
		free_cmds(*cmd);
		free_tokens(cmd->tokens);
		ft_clear_env(cmd->env);
		free(envp);
		ft_printf("exit\n");
		exit(exit_nbr);
	}
	else if (exit_code)
	{
		free_cmds(*cmd);
		free_tokens(cmd->tokens);
		ft_clear_env(cmd->env);
		free(envp);
		ft_putstr_fd("exit: numeric argument required\n", 2);
		exit(-1);
	}
	ft_printf("exit\n");
	exit(0);
}
