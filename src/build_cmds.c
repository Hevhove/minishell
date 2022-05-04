/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hendrik <Hendrik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:18:00 by Hendrik           #+#    #+#             */
/*   Updated: 2022/05/04 11:26:34 by Hendrik          ###   ########.fr       */
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

void	build_cmds(char **tokens, t_cmd *cmd) // echo "hello $PWD"|wc -l>>outfile
{
	int	i;

	cmd->argc = count_cmds(tokens);
	printf("cmd_arg is: %d\n", cmd->argc);
	cmd->scmds = (t_scmd *)malloc((cmd->argc + 1) * sizeof(t_scmd));
	if (!cmd->scmds)
		exit(2);
	i = 0;
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], "|", 1) != 0)
		{
			cmd->scmds[i].argv;
		}

	}
}
