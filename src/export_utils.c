/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:19:06 by mmaxime-          #+#    #+#             */
/*   Updated: 2022/05/19 12:12:22 by mmaxime-         ###   ########.fr       */
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
	while (*env)
	{
		if (!ft_strncmp(tokens[1], (*env)->content, ft_strlen(tokens[1])))
			return (1);
		*env = (*env)->next;
	}
	return (0);
}
