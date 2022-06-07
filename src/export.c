/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:29:52 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/07 20:58:13 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	export_no_var(t_list **env)
{
	t_list	*tmp;

	tmp = *env;
	while (tmp)
	{
		ft_("declare -x %s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}

static void	export_new_var(char *tokens, t_list **env)
{
	t_list	*new;

	new = ft_lstnew(ft_strdup(tokens));
	ft_lstadd_back(env, new);
}

int	already_in_env(char *tokens, t_list **env)
{
	char	*name;
	char	*value;
	int		i;

	if (!ft_isalpha(tokens[0]) && tokens[0] != '_')
		return (1);
	i = 1;
	while (tokens[i] && (ft_isalnum(tokens[i]) || tokens[i] == '_'))
		i++;
	if (tokens[i] && tokens[i] != '=')
		return (1);
	name = ft_substr(tokens, 0, i);
	value = NULL;
	if (tokens[i])
		value = ft_strdup(tokens + i + 1);
	if (get_env_value(name, env))
	{
		set_pwd_vars_env(name, value, env);
		free(name);
		free(value);
	}
	else
		export_new_var(tokens, env);
	return (0);
}

int	exec_export(char **tokens, t_list **env)
{
	int	i;

	if (!tokens[1])
	{
		export_no_var(env);
		return (0);
	}
	i = 1;
	while (tokens[i])
	{
		if (already_in_env(tokens[i], env))
		{
			ft_putstr_fd("Not a valid identifier\n", STDERR_FILENO);
			return (1);
		}
		i++;
	}
	return (0);
}
