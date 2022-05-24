/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:29:49 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/05/24 10:59:11 by mmaxime-         ###   ########.fr       */
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
	while (envp[i++])
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

void	exec_env(t_list **env)
{
	t_list	*tmp;

	tmp = *env;
	while (tmp)
	{
		printf("%s\n", (tmp)->content);
		tmp = tmp->next;
	}
}
