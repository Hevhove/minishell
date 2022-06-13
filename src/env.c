/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:29:49 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/13 17:54:01 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*handling_shlvl(char *var)
{
	char	*value;
	char	*name;
	int		i;

	i = 0;
	while (var[i] != '=')
		i++;
	name = ft_substr(var, 0, i + 1);
	value = ft_itoa(ft_atoi(var + i + 1) + 1);
	var = ft_strjoin(name, value);
	free(name);
	free(value);
	return (var);
}

void	env_init(t_cmd *cmd, char **envp)
{
	int		i;
	t_list	*node;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("SHLVL", envp[i], 5) == 0)
		{
			envp[i] = handling_shlvl(envp[i]);
			node = ft_lstnew(ft_strdup(envp[i]));
		}
		else
			node = ft_lstnew(ft_strdup(envp[i]));
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
		free(tmp->content);
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

int	exec_env(t_list **env)
{
	t_list	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strchr(tmp->content, '='))
				ft_printf("%s\n", (char *)(tmp->content));
		tmp = tmp->next;
	}
	return (0);
}
