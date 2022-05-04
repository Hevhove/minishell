/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:18:00 by Hendrik           #+#    #+#             */
/*   Updated: 2022/05/04 17:17:05 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_cmds(char **tokens)
{
	int i;
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
	int argc;

	argc = 0;
	if (ft_strncmp(tokens[index], "|", 1) == 0)
		index++;
	while (tokens[index] && ft_strncmp(tokens[index], "|", 1) != 0)
	{
		// careful here
		if (ft_strncmp(tokens[index], ">", 1) == 0
			|| ft_strncmp(tokens[index], ">>", 2) == 0
			|| ft_strncmp(tokens[index], "<", 1) == 0
			|| ft_strncmp(tokens[index], "<<", 2) == 0)
				index++;
		printf("index is %d\n", index);
		index++;
		argc++;
	}
	return (argc);
}

void	set_cmd_count(char **tokens, t_cmd *cmd)
{
	int	i;
	int	j;
	
	cmd->argc = count_cmds(tokens);
	cmd->scmds = (t_scmd *)malloc((cmd->argc + 1) * sizeof(t_scmd));
	if (!cmd->scmds)
		exit(2);
	i = 0;
	j = 0;
	while (tokens[i])
	{
		i = i + skip_token(tokens[i]);
		cmd->scmds[j].argc = scmd_arg_count(tokens, i);
		i += cmd->scmds[j++].argc;
	}
}

void	build_cmds(char **tokens, t_cmd *cmd) // echo "hello $PWD"|wc -l>>outfile
{
	int	i;

	set_cmd_count(tokens, cmd);
	printf("cmd_arg is: %d\n", cmd->argc);
	i = 0;
	while (i < cmd->argc)
	{
		printf("cmd_len is: %d\n", cmd->scmds[i++].argc);
	}
}
