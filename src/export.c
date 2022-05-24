/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:29:52 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/05/24 10:57:04 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	export_no_var(t_list **env)
{
	while (*env)
	{
		printf("declare -x %s\n", (*env)->content);
		*env = (*env)->next;
	}
}

int	already_in_env(char **tokens, t_list **env)
{
	t_list *tmp;
	
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
		printf("bash: export: `%s': not a valid identifier\n", tokens[1]);
		return (-1);
	}
	if (!ft_strchr(tokens[1], '='))
		return (-1);
	if (already_in_env(tokens, env) == 1)
		return (0);
	new = ft_lstnew(tokens[1]);
	ft_lstadd_back(env, new);
	return (1);
}
