/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:18:00 by Hendrik           #+#    #+#             */
/*   Updated: 2022/05/11 19:51:35 by hvan-hov         ###   ########.fr       */
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
		//printf("index is %d\n", index);
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
		printf("tokens[%d] is: %s\n", i, tokens[i]);
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
		//printf("i is: %d\n", i);
		//printf("argc is: %d\n", cmd->scmds[i].raw_argc);
		cmd->scmds[i].raw = (char **)malloc((cmd->scmds[i].raw_argc + 1) * sizeof(char *));
		while (j < cmd->scmds[i].raw_argc)
		{
			//printf("tokens[k] is: %s\n", tokens[k]);
			cmd->scmds[i].raw[j] = ft_strdup(tokens[k]);
			//printf("raw[j] is: %s\n", cmd->scmds[i].raw[j]);
			j++;
			k++;
		}
		cmd->scmds[i].raw[j] = NULL; // DOUBLECHECK
		if (tokens[k] && ft_strncmp(tokens[k], "|", 1) == 0)
			k++;
		i++;
	}
}

void	set_cmd_count(char **tokens, t_cmd *cmd)
{
	int	i;
	int	j;
	
	cmd->argc = count_cmds(tokens);
	cmd->scmds = (t_scmd *)malloc((cmd->argc + 1) * sizeof(t_scmd));
	if (!cmd->scmds)
		exit(2); // error codes?
	i = 0;
	j = 0;
	while (tokens[i])
	{
		i += raw_arg_count(cmd, tokens, i, j);
		if (tokens[i] && ft_strncmp(tokens[i], "|", 1) == 0)
			i++;
		j++;
	}
	// while (tokens[i])
	// {
	// 	i = i + skip_token(tokens[i]);
	// 	cmd->scmds[j].argc = scmd_arg_count(tokens, i);
	// 	i += cmd->scmds[j++].argc;
	// }
}

void	write_fds(t_cmd *cmd, char *fname, const char *mode, int pos)
{
	
	if (ft_strncmp(mode, ">>", 2) == 0)
	{
		if (cmd->scmds[pos].fd_out.fname) // needed if we have multiple times the same
			free(fname);
		cmd->scmds[pos].fd_out.fname = ft_strdup(fname);
		cmd->scmds[pos].append = 1;
	}
	else if (ft_strncmp(mode, "<<", 2) == 0)
	{
		if (cmd->scmds[pos].fd_in.fname) // needed if we have multiple times the same
			free(fname);
		cmd->scmds[pos].fd_in.fname = ft_strdup(fname);
		cmd->scmds[pos].heredoc = 1;
	}
	else if (ft_strncmp(mode, ">", 1) == 0)
	{
		if (cmd->scmds[pos].fd_out.fname) // needed if we have multiple times the same
			free(fname);
		cmd->scmds[pos].fd_out.fname = ft_strdup(fname);
	}
	else if (ft_strncmp(mode, "<", 1) == 0)
	{
		if (cmd->scmds[pos].fd_out.fname) // needed if we have multiple times the same
			free(fname);
		cmd->scmds[pos].fd_in.fname = ft_strdup(fname);
	}
}

void	update_fds(t_cmd *cmd)
{
	int	i;
	int	j;
	
	i = 0;
	while (i < cmd->argc)
	{
		j = 0;
		while (j < cmd->scmds[i].raw_argc)
		{
			cmd->scmds[i].append = 0;
			cmd->scmds[i].heredoc = 0;
			cmd->scmds[i].fd_in.fname = NULL;
			cmd->scmds[i].fd_out.fname = NULL;
			cmd->scmds[i].fd_err.fname = NULL;
			if (cmd->scmds[i].raw[j] && ft_strncmp(cmd->scmds[i].raw[j], ">>", 2) == 0)
				write_fds(cmd, cmd->scmds[i].raw[++j], ">>", i);
			else if (cmd->scmds[i].raw[j] && ft_strncmp(cmd->scmds[i].raw[j], "<<", 2) == 0)
				write_fds(cmd, cmd->scmds[i].raw[++j], "<<", i);
			else if (cmd->scmds[i].raw[j] && ft_strncmp(cmd->scmds[i].raw[j], ">", 1) == 0)
				write_fds(cmd, cmd->scmds[i].raw[++j], ">", i);
			else if (cmd->scmds[i].raw[j] && ft_strncmp(cmd->scmds[i].raw[j], "<", 1) == 0)
				write_fds(cmd, cmd->scmds[i].raw[++j], "<", i);
			j++;
		}
		i++;
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
		// if (ft_strncmp(scmd.raw[i], ">>", 2) == 0)
		// 	i++;
		// else if (ft_strncmp(scmd.raw[i], "<<", 2) == 0)
		// 	i++;
		// else if (ft_strncmp(scmd.raw[i], ">", 1) == 0)
		// 	i++;
		// else if (ft_strncmp(scmd.raw[i], "<", 1) == 0)
		// 	i++;
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
	
	i = 0;
	while (i < cmd->argc)
	{
		j = 0;
		k = 0;
		cmd->scmds[i].argc = count_argv(cmd->scmds[i]);
		cmd->scmds[i].argv = (char **)malloc((cmd->scmds[i].argc + 1) * sizeof(char *));
		while (j < cmd->scmds[i].raw_argc && k < cmd->scmds[i].argc)
		{
			if (check_token_type(cmd->scmds[i].raw[j][0]) != 1)
				cmd->scmds[i].argv[k] = ft_strdup(cmd->scmds[i].raw[j]);
			else
				j++;
			j++;
			k++;
		}
		cmd->scmds[i].argv[k] = NULL;
		i++;
	}
	// set last iteration?
}

void	build_cmds(char **tokens, t_cmd *cmd) // echo "hello $PWD"|wc -l>>outfile
{
	int	i;
	int j;
	
	set_cmd_count(tokens, cmd);
	write_raw_cmds(cmd, tokens);
	update_fds(cmd);
	rm_redirs(cmd);
	printf("cmd_arg is: %d\n", cmd->argc);
	i = 0;
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
	printf("check fd[%d] is: %s\n", 1, cmd->scmds[1].fd_out.fname);
	printf("check fd[%d] is: %s\n", 0, cmd->scmds[0].fd_in.fname);
	i = 0;
	printf("check argv: %d\n", cmd->scmds[1].raw_argc);
	printf("check argv: %d\n", cmd->scmds[1].argc);
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
