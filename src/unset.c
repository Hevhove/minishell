/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:29:57 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/07 12:08:21 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	rm_env_var(t_list **env)
{
	t_list	*tmp;

	tmp = (*env)->next;
	(*env)->next = (*env)->next->next;
	free(tmp);
}

int	exec_unset(char **tokens, t_list **env)
{
	char	*var_equal;
	t_list	*head;

	if (!tokens[1])
		return (-1);
	if (ft_strchr(tokens[1], '='))
	{
		ft_printf("unset error: `%s': not a valid identifier\n", tokens[1]);
		return (-1);
	}
	var_equal = ft_strjoin(tokens[1], "=");
	head = *env;
	while (*env)
	{
		if (!ft_strncmp(var_equal, (*env)->next->content, ft_strlen(var_equal)))
		{
			rm_env_var(env);
			*env = head;
			ft_free(&var_equal);
			return (1);
		}
		(*env) = (*env)->next;
	}
	ft_free(&var_equal);
	return (0);
}
