/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:29:57 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/08 16:42:13 by mmaxime-         ###   ########.fr       */
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

static int	check_name_var(char *name, t_list *tmp)
{
	int		i;
	char	*name_env;

	i = 0;
	if (!ft_strncmp(name, tmp->content, ft_strlen(name)))
	{
		name_env = tmp->content;
		while (name_env[i] && (name_env[i] != '='))
			i++;
		if (ft_strlen(name) == (size_t)i)
			return (1);
	}
	return (0);
}

int	exec_unset(char **tokens, t_list **env)
{
	char	*name;
	t_list	*tmp;
	int		i;
	int		j;

	i = 0;
	while (tokens[++i])
	{
		if (check_identifier(tokens[i]))
			return (1);
		j = 0;
		tmp = *env;
		while (tokens[i][j] && (ft_isalnum(tokens[i][j]) || tokens[i][j] == '_'))
			j++;
		name = ft_substr(tokens[i], 0, j);
		while (tmp)
		{
			if (check_name_var(name, tmp))
				rm_env_var(tmp, env);
			tmp = tmp->next;
		}
		ft_free(&name);
	}
	return (0);
}
