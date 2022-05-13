/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmds_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 19:26:24 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/05/13 19:27:06 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_cmds(char **tokens)
{
	int	i;
	int	cmd_no;

	i = 0;
	cmd_no = 1;
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], "|", 1) == 0)
			cmd_no++;
		i++;
	}
	return (cmd_no);
}

int	skip_token(char *token)
{
	if (ft_strncmp(token, "|", 1) == 0)
		return (1);
	else if (ft_strncmp(token, ">", 1) == 0
		|| ft_strncmp(token, "<", 1) == 0)
		return (2);
	else if (ft_strncmp(token, ">>", 2) == 0
		|| ft_strncmp(token, "<<", 2) == 0)
		return (2);
	return (0);
}

int	scmd_arg_count(char **tokens, int index)
{
	int	argc;

	argc = 0;
	if (ft_strncmp(tokens[index], "|", 1) == 0)
		index++;
	while (tokens[index] && ft_strncmp(tokens[index], "|", 1) != 0)
	{
		if (ft_strncmp(tokens[index], ">", 1) == 0
			|| ft_strncmp(tokens[index], ">>", 2) == 0
			|| ft_strncmp(tokens[index], "<", 1) == 0
			|| ft_strncmp(tokens[index], "<<", 2) == 0)
				index++;
		index++;
		argc++;
	}
	return (argc);
}

int	raw_arg_count(t_cmd *cmd, char **tokens, int i, int j)
{
	int	count;

	count = 0;
	while (tokens[i] && ft_strncmp(tokens[i], "|", 1) != 0)
	{
		count++;
		i++;
	}
	cmd->scmds[j].raw_argc = count;
	return (count);
}

void	write_raw_cmds(t_cmd *cmd, char **tokens)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (i < cmd->argc)
	{
		j = 0;
		cmd->scmds[i].raw = (char **)malloc((cmd->scmds[i].raw_argc + 1)
				* sizeof(char *));
		while (j < cmd->scmds[i].raw_argc)
		{
			cmd->scmds[i].raw[j] = ft_strdup(tokens[k]);
			j++;
			k++;
		}
		cmd->scmds[i].raw[j] = NULL;
		if (tokens[k] && ft_strncmp(tokens[k], "|", 1) == 0)
			k++;
		i++;
	}
}
