/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:29:52 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/05/23 19:30:44 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
