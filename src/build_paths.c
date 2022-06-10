/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 15:19:13 by Hendrik           #+#    #+#             */
/*   Updated: 2022/06/10 12:53:16 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*find_path(t_list **env)
{
	char	*line;
	t_list	*tmp;

	tmp = *env;
	line = NULL;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, "PATH", 4) == 0)
		{
			line = ft_strdup(tmp->content + 5);
			return (line);
		}
		tmp = tmp->next;
	}
	return (line);
}

char	*get_bin(char **paths, char *bin)
{
	int		i;
	char	*inter;
	char	*cmd_path;

	i = -1;
	if (ft_strcmp(bin, ".") == 0 || ft_strcmp(bin, "..") == 0)
		return (NULL);
	if (access(bin, F_OK) == 0)
		return (bin);
	if (bin[0] != '/' && paths)
	{
		while (paths[++i])
		{
			inter = ft_strjoin(paths[i], "/");
			cmd_path = ft_strjoin(inter, bin);
			free(inter);
			if (access(cmd_path, F_OK) == 0)
				return (cmd_path);
			free(cmd_path);
		}
	}
	return (NULL);
}

int	build_paths(t_cmd *cmd)
{
	char	*paths_str;

	paths_str = find_path(cmd->env);
	cmd->paths = ft_split(paths_str, ':');
	free(paths_str);
	return (0);
}

void	free_split(char	**split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return ;
}
