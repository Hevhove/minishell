/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:13:18 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/13 17:50:12 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	verify_redir(char *curr, char *next)
{
	if ((ft_strncmp(curr, ">", 1) == 0) && (ft_strncmp(next, "|", 1) == 0))
		return (-1);
	if ((ft_strncmp(curr, "<", 1) == 0) && (ft_strncmp(next, "|", 1) == 0))
		return (-1);
	if ((ft_strncmp(curr, "<", 1) == 0) && (ft_strncmp(next, "<", 1) == 0))
		return (-1);
	if ((ft_strncmp(curr, "<", 1) == 0) && (ft_strncmp(next, ">", 1) == 0))
		return (-1);
	if ((ft_strncmp(curr, ">", 1) == 0) && (ft_strncmp(next, ">", 1) == 0))
		return (-1);
	if ((ft_strncmp(curr, ">", 1) == 0) && (ft_strncmp(next, "<", 1) == 0))
		return (-1);
	return (0);
}

int	check_even_quotes(char	*token)
{
	int	i;
	int	squote_count;
	int	dquote_count;

	i = 0;
	squote_count = 0;
	dquote_count = 0;
	while (token[i])
	{
		if (token[i] == '\'')
			squote_count++;
		if (token[i] == '\"')
			dquote_count++;
		i++;
	}
	if (squote_count % 2 != 0 || dquote_count % 2 != 0)
		return (-1);
	return (0);
}

int	check_start_and_end(char **t, int i)
{
	if (ft_strncmp(t[i - 1], ">", 1) == 0 || ft_strncmp(t[i - 1], "<", 1) == 0)
	{
		ft_printf("parse error: unexpected token\n");
		return (0);
	}
	if (t[i + 1] && (ft_strncmp(t[0], "|", 1) == 0
			|| (i >= 1 && ft_strncmp(t[i - 1], "|", 1) == 0)))
	{
		ft_printf("parse error: unexpected token\n");
		return (0);
	}
	return (1);
}

int	verify_tokens(char	**t)
{
	int	i;

	i = 0;
	if (t[i] == NULL)
		return (0);
	while (t[i])
	{
		if (check_even_quotes(t[i]) < 0)
		{
			ft_printf("parse error: no closing quote found\n");
			return (0);
		}
		if (t[i + 1] && (((ft_strncmp(t[i], "|", 1) == 0)
					&& (ft_strncmp(t[i + 1], "|", 1) == 0))
				|| (verify_redir(t[i], t[i + 1]) < 0)))
		{
			ft_printf("parse error: unexpected token\n");
			return (0);
		}
		i++;
	}
	if (!check_start_and_end(t, i))
		return (0);
	return (1);
}

int	check_heredocs(t_cmd cmd)
{
	int	i;
	int	heredoc_count;

	i = 0;
	heredoc_count = 0;
	while (i < cmd.argc)
	{
		if (cmd.scmds[i].heredoc == 1)
			heredoc_count++;
		i++;
	}
	return (heredoc_count);
}
