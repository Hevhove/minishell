/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:29:49 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/05 12:02:09 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	env_init(t_cmd *cmd, char **envp)
{
	int		i;
	t_list	*node;

	i = 0;
	while (envp[i])
	{
		node = ft_lstnew(envp[i]);
		ft_lstadd_back(cmd->env, node);
		i++;
	}
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
			var_value = ft_substr(to_get->content, name_len,
					ft_strlen(to_get->content) - name_len);
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
		printf("%s\n", (char *)(tmp->content));
		tmp = tmp->next;
	}
}
