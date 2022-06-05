/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:12:22 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/02 17:08:06 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_list_len(t_list **env)
{
	int		count;
	t_list	*tmp;

	count = 0;
	tmp = *env;
	while (tmp != NULL)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**create_envp(t_list **env)
{
	t_list	*tmp;
	char	**envp;
	int		count;
	int		i;

	tmp = *env;
	count = count_list_len(env);
	envp = (char **)malloc((count + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	while (i < count)
	{
		envp[i] = tmp->content;
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}
