/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:18:00 by Hendrik           #+#    #+#             */
/*   Updated: 2022/05/22 14:50:52 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
TODO: AT EVERY MALLOC, CHECK IF RETURN IS NOT NULL
TODO: FREEING AFTER FAIL AND AT END OF PROGRAM?
TODO: ERROR MANAGEMENT...
*/

void	print_raw_commands(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (i < cmd->argc)
	{
		j = 0;
		while (j < cmd->scmds[i].raw_argc)
		{
			printf("current command [%d][%d] is: %s\n",
				i, j, cmd->scmds[i].raw[j]);
			j++;
		}
		i++;
	}
}

void	print_commands(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < cmd->argc)
	{
		j = 0;
		while (j < cmd->scmds[i].argc)
		{
			printf("current command2 [%d][%d] is: %s\n",
				i, j, cmd->scmds[i].argv[j]);
			j++;
		}
		i++;
	}
}

void	print_fds(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->argc)
	{
		printf("current fd_in [%d] is: %s\n", i, cmd->scmds[i].fd_in.fname);
		printf("current fd_out [%d] is: %s\n", i, cmd->scmds[i].fd_out.fname);
		printf("current fd_err [%d] is: %s\n", i, cmd->scmds[i].fd_err.fname);
		printf("Append status [%d] is: %d\n", i, cmd->scmds[i].append);
		printf("Heredoc status [%d] is: %d\n", i, cmd->scmds[i].heredoc);
		i++;
	}
}

void	rm_redirs(t_cmd *cmd)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (++i < cmd->argc)
	{
		cmd->scmds[i].argc = count_argv(cmd->scmds[i]);
		cmd->scmds[i].argv = (char **)malloc((cmd->scmds[i].argc + 1)
				* sizeof(char *));
		j = 0;
		k = 0;
		while (j < cmd->scmds[i].raw_argc && k < cmd->scmds[i].argc)
		{
			if (check_token_type(cmd->scmds[i].raw[j][0]) != 1)
			{
				cmd->scmds[i].argv[k] = ft_strdup(cmd->scmds[i].raw[j]);
				k++;
			}
			else
				j++;
			j++;
		}
		cmd->scmds[i].argv[k] = NULL;
	}
}

void	build_cmds(char **tokens, t_cmd *cmd)
{
	set_cmd_count(tokens, cmd);
	write_raw_cmds(cmd, tokens);
	update_fds(cmd);
	rm_redirs(cmd);
	//printf("cmd_arg is: %d\n", cmd->argc);
	//printf("------------\n");
	//print_raw_commands(cmd);
	//printf("------------\n");
	//print_fds(cmd);
	//printf("------------\n");
	//print_commands(cmd);
	//printf("------------\n");
}
