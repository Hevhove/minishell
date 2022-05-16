/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:07:14 by mmaxime-          #+#    #+#             */
/*   Updated: 2022/05/13 10:40:02 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// char	**get_env_list(char **envp)
// {
// 	int		line;
// 	int		line_nb;
// 	char	**env_list;

// 	line = 0;
// 	line_nb = 0;
// 	while (envp[line++])
// 		line_nb++;
// 	env_list = malloc(sizeof(char *) * (line_nb + 1));
// 	if (!env_list)
// 		return (NULL);
// 	line = 0;
// 	while (line < line_nb)
// 	{
// 		env_list[line] = ft_strdup(envp[line]);
// 		line++;
// 	}
// 	env_list[line] = NULL;
// 	return (env_list);
// }

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

// int	main(int argc, char **argv, char **envp)
// {	
// 	t_list	**env;

// 	env = (t_list **)malloc(sizeof(t_list));
// 	if (!env)
// 		return (-1);
// 	*env = NULL;
// 	env_init(env, envp);
// 	while ((*env)->next)
// 	{
// 		printf("%s\n", (*env)->content);
// 		env = &(*env)->next;
// 	}
// 	return (0);
// }