/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:29:52 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/07 12:05:27 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	export_no_var(t_list **env)
{
	t_list	*tmp;

	tmp = *env;
	while (tmp)
	{
		printf("declare -x %s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}

int	already_in_env(char **tokens, t_list **env)
{
	t_list	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tokens[1], (tmp)->content, ft_strlen(tokens[1])))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	exec_export(char **tokens, t_list **env)
{
	t_list	*new;

	if (!tokens[1])
	{
		export_no_var(env);
		return (0);
	}
	if (ft_isdigit((int)tokens[1][0]))
	{
		ft_printf("export error: `%s': not a valid identifier\n", tokens[1]);
		return (-1);
	}
	if (!ft_strchr(tokens[1], '='))
	{
		ft_putstr_fd("export error: no '=' sign found\n", 2);
		return (-1);
	}
	if (already_in_env(tokens, env) == 1)
		return (0);
	new = ft_lstnew(ft_strdup(tokens[1]));
	ft_lstadd_back(env, new);
	return (1);
}
