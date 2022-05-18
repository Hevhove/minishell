/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:07:14 by mmaxime-          #+#    #+#             */
/*   Updated: 2022/05/18 13:36:59 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	env_init(t_list **env, char **envp)
{
	t_list	*new;
	int		i;
	int		lines_nb;

	i = 0;
	lines_nb = 0;
	while (envp[i++]) // envp[9]
		lines_nb++;
	i = 0;
	while (i < lines_nb)
	{
		new = ft_lstnew(envp[i]);
		ft_lstadd_back(env, new);
		i++;
	}
	return ;
}

void	ft_clear_env(t_list **env)
{
	t_list	*tmp;

	while (*env != NULL)
	{
		tmp = *env;
		*env = (*env)->next;
		free(tmp);
	}
	free(env);
}
