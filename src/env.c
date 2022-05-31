/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:29:49 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/05/24 16:17:11 by mmaxime-         ###   ########.fr       */
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

char	*get_env_value(char *name, t_list **env)
{
	t_list	*to_get;
	char	*var_name;
	char	*var_value;
	size_t	name_len;

	to_get = *env;
	var_name = ft_strjoin(name, "=");
	name_len = ft_strlen(var_name);
	while (to_get)
	{
		if (!ft_strncmp(var_name, to_get->content, name_len))
		{
			var_value = ft_substr(to_get->content, name_len, ft_strlen(to_get->content) - name_len);
			ft_free(&var_name);
			to_get = NULL;
			return (var_value);
		}
		to_get = to_get->next; 
	}
	ft_free(&var_name);
	to_get = NULL;
	return (NULL);
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
