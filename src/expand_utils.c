/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:20:45 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/05 12:53:04 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_var_name(char	*token)
{
	int		i;
	char	*var_name;

	i = 0;
	while (token[i] && token[i] != '\"')
		i++;
	var_name = (char *)malloc((i * sizeof(char)) + 1);
	if (!var_name)
		return (NULL);
	i = 0;
	while (token[i] && token[i] != '\"')
	{
		var_name[i] = token[i];
		i++;
		if (token[i + 1] && token[i] == '\'' && token[i + 1] == '\"')
			break ;
	}
	var_name[i] = '\0';
	return (var_name);
}

char	*fill_expanded_name(char *line, int index)
{
	int		i;
	char	*exp_name;

	i = 0;
	while (line[index + i])
		i++;
	exp_name = (char *)malloc((i + 1) * sizeof(char));
	i = 0;
	while (line[index + i])
	{
		exp_name[i] = line[index + i];
		i++;
	}
	exp_name[i] = '\0';
	return (exp_name);
}

char	*get_expanded_name(char	*var_name, t_list **env)
{
	t_list	*tmp;
	int		i;
	char	*expanded_name;

	tmp = *env;
	expanded_name = NULL;
	while (tmp != NULL)
	{
		i = 0;
		while (((char *)tmp->content)[i] && ((char *)tmp->content)[i] != '=')
			i++;
		if (ft_strncmp(var_name, (char *)tmp->content, ft_strlen(var_name)) == 0)
			expanded_name = fill_expanded_name((char *)tmp->content, i + 1);
		if (!expanded_name)
		{
			expanded_name = (char *)malloc(1 * sizeof(char));
			expanded_name[0] = '\0';
		}
		tmp = tmp->next;
	}
	return (expanded_name);
}

char	*get_prestring(char	*token)
{
	int		i;
	char	*pre;

	i = 0;
	while (token[i] && token[i] != '$')
		i++;
	pre = (char *)malloc(i * sizeof(char) + 1);
	i = 0;
	while (token[i] && token[i] != '$')
	{
		pre[i] = token[i];
		i++;
	}
	pre[i] = '\0';
	return (pre);
}

char	*get_poststring(char *token)
{
	int		i;
	int		j;
	int		len;
	char	*post;

	i = 0;
	while (token[i] && token[i] != '$')
		i++;
	while (token[i] && token[i] != '\"')
	{
		if (token[i] == '\'' && token[i + 1] == '\"')
			break ;
		i++;
	}
	len = 0;
	while (token[i++])
		len++;
	post = (char *)malloc(len * sizeof(char) + 1);
	j = 0;
	i = i - len - 1;
	while (j < len)
		post[j++] = token[i++];
	post[j] = '\0';
	return (post);
}
