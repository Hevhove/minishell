/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmds_utils3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:50:45 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/13 16:51:50 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_split(char	**split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		ft_printf("split is: %s\n", split[i]);
		i++;
	}
	return ;
}

int	update_empty_heredoc_cmds(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->argc)
	{
		if (cmd->scmds[i].heredoc == 1 && cmd->scmds[i].argc == 0)
		{
			move_delims(&(cmd->scmds[i]), i);
			heredoc_input((*cmd), (*cmd).scmds[i].delim, i);
			return (-1);
		}
		else if (cmd->scmds[i].argc == 0)
			return (-1);
		i++;
	}
	return (0);
}
