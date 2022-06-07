/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:29:57 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/07 21:41:08 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	rm_env_var(t_list *node, t_list **env)
{
	t_list	*tmp;

	tmp = *env;
	while (tmp->next)
	{
		if (tmp->next == node)
		{
			free(tmp->next);
			tmp->next = tmp->next->next;
			return ;
		}
		tmp = tmp->next;
	}
}

static int	check_identifier(char *tokens)
{
	int	i;

	if (!ft_isalnum(tokens[0]) && tokens[0] != '_')
	{
		ft_putstr_fd("unset error: not a valid identifier\n", 2);
		return (1);
	}
	i = 1;
	while (tokens[i])
	{
		if (!ft_isalnum(tokens[i]) && tokens[i] != '_')
		{
			ft_putstr_fd("unset error: not a valid identifier\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	exec_unset(char **tokens, t_list **env)
{
	char	*var_equal;
	t_list	*tmp;
	int		i;

	i = 0;
	while (tokens[++i])
	{
		if (check_identifier(tokens[i]))
			return (1);
		var_equal = ft_strjoin(tokens[i], "=");
		tmp = *env;
		while (tmp)
		{
			if (!ft_strncmp(var_equal, tmp->content, ft_strlen(var_equal)))
				rm_env_var(tmp, env);
			tmp = tmp->next;
		}
		ft_free(&var_equal);
	}
	return (0);
}
