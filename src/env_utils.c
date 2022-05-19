/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:07:14 by mmaxime-          #+#    #+#             */
/*   Updated: 2022/05/19 14:08:04 by mmaxime-         ###   ########.fr       */
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

void	rm_env_var(t_list **env)
{
	t_list	*tmp;

	tmp = (*env)->next;
	(*env)->next = (*env)->next->next;
	free(tmp);
}

void	set_pwd_vars_env(char *old_pwd, char *new_pwd, t_list **env)
{
	char	*var_old_pwd;
	char	*var_pwd;
	t_list	*head;

	var_old_pwd = ft_strjoin("OLDPWD=", old_pwd);
	var_pwd = ft_strjoin("PWD=", new_pwd);
	head = *env;
	while (!ft_strncmp((*env)->content, "OLDPWD=", 7))
		*env = (*env)->next;
	(*env)->content = var_old_pwd;
	*env = head;
	while (!ft_strncmp((*env)->content, "PWD=", 4))
		*env = (*env)->next;
	(*env)->content = var_pwd;
	*env = head;
	ft_free(&var_old_pwd);
	ft_free(&var_pwd);
	return ;
}
