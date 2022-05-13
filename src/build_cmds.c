/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:18:00 by Hendrik           #+#    #+#             */
/*   Updated: 2022/05/13 13:57:00 by hvan-hov         ###   ########.fr       */
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

/*
TODO: AT EVERY MALLOC, CHECK IF RETURN IS NOT NULL
TODO: FREEING AFTER FAIL AND AT END OF PROGRAM?
TODO: ERROR MANAGEMENT...
*/

void	set_cmd_count(char **tokens, t_cmd *cmd)
{
	int	i;
	int	j;

	cmd->argc = count_cmds(tokens);
	cmd->scmds = (t_scmd *)malloc((cmd->argc) * sizeof(t_scmd)); //[scmd1 scmd2]
	if (!cmd->scmds)
		exit(2);
	i = 0;
	j = 0;
	while (tokens[i])
	{
		i += raw_arg_count(cmd, tokens, i, j);
		if (tokens[i] && ft_strncmp(tokens[i], "|", 1) == 0)
			i++;
		j++;
	}
}

/*
	In below function, should we still free 
	in case of echo "hello" > outfile >> outfile2?
	we might overwrite fname here which is a strdup causing memleak
*/

void	write_fds(t_cmd *cmd, const char *fname, const char *mode, int pos)
{
	if (ft_strncmp(mode, ">>", 2) == 0)
	{
		//free(cmd->scmds[pos].fd_out.fname);
		cmd->scmds[pos].fd_out.fname = ft_strdup(fname);
		cmd->scmds[pos].append = 1;
	}
	else if (ft_strncmp(mode, "<<", 2) == 0)
	{
		//free(cmd->scmds[pos].fd_in.fname);
		cmd->scmds[pos].fd_in.fname = ft_strdup(fname);
		cmd->scmds[pos].heredoc = 1;
	}
	else if (ft_strncmp(mode, ">", 1) == 0)
	{
		//free(cmd->scmds[pos].fd_out.fname);
		cmd->scmds[pos].fd_out.fname = ft_strdup(fname);
	}
	else if (ft_strncmp(mode, "<", 1) == 0)
	{
		//free(cmd->scmds[pos].fd_in.fname);
		cmd->scmds[pos].fd_in.fname = ft_strdup(fname);
	}
}

void	init_scmd_fds(t_cmd *cmd, int i)
{
	cmd->scmds[i].append = 0;
	cmd->scmds[i].heredoc = 0;
	cmd->scmds[i].fd_in.fname = NULL;
	cmd->scmds[i].fd_out.fname = NULL;
	cmd->scmds[i].fd_err.fname = NULL;
}

void	update_fds(t_cmd *cmd)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cmd->argc)
	{
		j = -1;
		init_scmd_fds(cmd, i);
		while (++j < cmd->scmds[i].raw_argc)
		{
			if (cmd->scmds[i].raw[j]
				&& ft_strncmp(cmd->scmds[i].raw[j], ">>", 2) == 0)
				write_fds(cmd, cmd->scmds[i].raw[++j], ">>", i);
			else if (cmd->scmds[i].raw[j]
				&& ft_strncmp(cmd->scmds[i].raw[j], "<<", 2) == 0)
				write_fds(cmd, cmd->scmds[i].raw[++j], "<<", i);
			else if (cmd->scmds[i].raw[j]
				&& ft_strncmp(cmd->scmds[i].raw[j], ">", 1) == 0)
				write_fds(cmd, cmd->scmds[i].raw[++j], ">", i);
			else if (cmd->scmds[i].raw[j]
				&& ft_strncmp(cmd->scmds[i].raw[j], "<", 1) == 0)
				write_fds(cmd, cmd->scmds[i].raw[++j], "<", i);
		}
	}
}

int	count_argv(t_scmd scmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (scmd.raw[i])
	{
		if (check_token_type(scmd.raw[i][0]) == 1)
		{
			i += 2;
			continue ;
		}
		count++;
		i++;
	}
	return (count);
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
	int	i;
	int	j;

	set_cmd_count(tokens, cmd);
	write_raw_cmds(cmd, tokens);
	update_fds(cmd);
	rm_redirs(cmd);
	printf("cmd_arg is: %d\n", cmd->argc);
	i = 0;
	printf("------------\n");
	while (i < cmd->argc)
	{
		j = 0;
		while (j < cmd->scmds[i].raw_argc)
		{
			printf("current command [%d][%d] is: %s\n", i, j, cmd->scmds[i].raw[j]);
			j++;
		}
		i++;
	}
	printf("------------\n");
	printf("STATUS CHECK: %d\n", cmd->scmds[0].append);
	// FD CHECK
	i = 0;
	while (i < cmd->argc)
	{
		printf("current fd_in [%d] is: %s\n", i, cmd->scmds[i].fd_in.fname);
		printf("current fd_out [%d] is: %s\n", i, cmd->scmds[i].fd_out.fname);
		printf("current fd_err [%d] is: %s\n", i, cmd->scmds[i].fd_err.fname);
		i++;
	}
	printf("------------\n");
	i = 0;
	//printf("check argv: %d\n", cmd->scmds[1].raw_argc);
	//printf("check argv: %d\n", cmd->scmds[1].argc);
	while (i < cmd->argc)
	{
		j = 0;
		while (j < cmd->scmds[i].argc)
		{
			printf("current command2 [%d][%d] is: %s\n", i, j, cmd->scmds[i].argv[j]);
			j++;
		}
		i++;
	}
}
