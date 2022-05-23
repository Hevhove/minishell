/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:13:40 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/05/23 10:13:57 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	create_pipes(t_cmd *cmd)
{
	int	i;
	int pipe_num;

	pipe_num = 2 * (cmd->argc - 1);
	i = 0;
	if (pipe_num > 0) // CHECK VALGRIND -> INVALID WRITE??
	{
		cmd->pipes = (int *)malloc((pipe_num) * sizeof(int));
		if (!cmd->pipes)
			; // some error code;
		while (i < cmd->argc - 1)
		{
			if (pipe(cmd->pipes + 2 * i) < 0)
				; // free the parent or something
			i++;
		}
	}
	return ;
}

void	close_pipes(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < ( 2 * (cmd->argc - 1)))
	{
		close(cmd->pipes[i]);
		i++;
	}
}