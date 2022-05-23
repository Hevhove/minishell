/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:19:06 by mmaxime-          #+#    #+#             */
/*   Updated: 2022/05/23 13:05:01 by hvan-hov         ###   ########.fr       */
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
