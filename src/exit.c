/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:50:13 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/10 17:34:43 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_isnumber(char	*str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9')
			|| str[i] == '\'' || str[i] == '\"')
			i++;
		else
			return (0);
	}
	return (1);
}

void	non_num_arg(t_cmd *cmd, char **envp)
{
	free_cmds(*cmd);
	free_tokens(cmd->tokens);
	ft_clear_env(cmd->env);
	free(envp);
	ft_putstr_fd("exit: numeric argument required\n", 2);
}

int	normal_exit(t_cmd *cmd, char *exit_code, char **envp)
{
	int	exit_nbr;

	exit_nbr = ft_atoi(exit_code);
	free_cmds(*cmd);
	free_tokens(cmd->tokens);
	ft_clear_env(cmd->env);
	free(envp);
	return (exit_nbr);
}

void	exit_no_arg(t_cmd *cmd, char **envp)
{
	free_cmds(*cmd);
	free_tokens(cmd->tokens);
	ft_clear_env(cmd->env);
	free(envp);
}

void	ft_exit(t_cmd *cmd, char **envp)
{
	char	*exit_code;
	int		exit_nbr;

	exit_code = cmd->scmds[0].argv[1];
	ft_printf("exit\n");
	if (cmd->scmds[0].argc > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return ;
	}
	if (exit_code && ft_isnumber(exit_code))
	{
		exit_nbr = normal_exit(cmd, exit_code, envp);
		exit(exit_nbr);
	}
	else if (exit_code)
	{
		non_num_arg(cmd, envp);
		exit(-1);
	}
	exit_no_arg(cmd, envp);
	exit(0);
}
