/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:19:06 by mmaxime-          #+#    #+#             */
/*   Updated: 2022/05/17 13:09:39 by mmaxime-         ###   ########.fr       */
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

int	check_in_env(t_list *new, t_list **env)
{
	while (*env)
	{
		if (strncmp(new->content, (*env)->content, ft_strlen(new->content)) == 0)
			return (1);
		*env = (*env)->next;
	}
	return (0);
}