/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:05:53 by mmaxime-          #+#    #+#             */
/*   Updated: 2022/05/17 13:47:33 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exec_unset(char **tokens, t_list **env)
{
	if (!tokens[1])
		return (-1);
	if (ft_strchr(tokens[1], '='))
	{
		printf("bash: unset: `%s': not a valid identifier\n", tokens[1]);
		return (-1);
	}
	while (*env)
	{
		if (ft_strncmp(tokens[1], (*env)->content, ft_strlen(tokens[1]) == 0))
		{
			ft_lstdelone(*env, (*env)->content);
			*env = (*env)->next;
			return (1);
		}
		*env = (*env)->next;
	}
	return (0);
}
