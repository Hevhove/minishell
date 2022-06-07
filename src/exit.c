/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:50:13 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/07 10:46:21 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_exit(t_cmd *cmd, char **envp)
{
	free_cmds(*cmd);
	free_tokens(cmd->tokens);
	ft_clear_env(cmd->env);
	free(envp);
	printf("exit\n");
	exit (0);
}
