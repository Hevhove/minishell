/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:13:40 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/07 12:05:37 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	create_pipes(t_cmd *cmd)
{
	int	i;
	int	pipe_num;

	pipe_num = 2 * (cmd->argc - 1);
	i = 0;
	if (pipe_num > 0)
	{
		cmd->pipes = (int *)malloc((pipe_num) * sizeof(int));
		if (!cmd->pipes)
			return (-1);
		while (i < cmd->argc - 1)
		{
			if (pipe(cmd->pipes + 2 * i) < 0)
				return (-1);
			i++;
		}
	}
	return (0);
}

int	close_pipes(t_cmd *cmd)
{
	int	i;
	int	ret;

	i = 0;
	while (i < (2 * (cmd->argc - 1)))
	{
		ret = close(cmd->pipes[i]);
		if (ret < 0)
			return (-1);
		i++;
	}
	return (0);
}
