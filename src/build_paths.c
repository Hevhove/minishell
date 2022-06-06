/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 15:19:13 by Hendrik           #+#    #+#             */
/*   Updated: 2022/06/06 17:42:48 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*find_path(t_list **env)
{
	char	*line;
	t_list	*tmp;

	tmp = *env;
	line = NULL;
	while (tmp->next != NULL)
	{
		if (ft_strncmp(tmp->content, "PATH", 4) == 0)
		{
			line = ft_strdup(tmp->content + 5);
			return (line);
		}
		tmp = tmp->next;
	}
	printf("path not found\n");
	return (line);
}

char	*get_bin(char **paths, char *bin)
{
	int		i;
	char	*inter;
	char	*cmd_path;

	i = 0;
	if (bin[0] != '/')
	{
		while (paths[i])
		{
			inter = ft_strjoin(paths[i], "/");
			cmd_path = ft_strjoin(inter, bin);
			free(inter);
			if (access(cmd_path, F_OK) == 0)
				return (cmd_path);
			free(cmd_path);
			i++;
		}
	}
	else
	{
		if (access(bin, F_OK) == 0)
			return (bin);
	}
	return (NULL);
}

int	build_paths(t_cmd *cmd)
{
	char	*paths_str;

	paths_str = find_path(cmd->env);
	cmd->paths = ft_split(paths_str, ':');
	free(paths_str);
	if (!cmd->paths)
	{
		ft_printf("failed to build the paths variable\n");
		return (-1);
	}
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
