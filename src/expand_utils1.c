/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:20:45 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/13 18:22:48 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_var_name(char	*token)
{
	int		i;
	char	*var_name;

	i = 0;
	while (token[i] && !cst(token[i])
		&& !is_expand_exception(token[i]))
		i++;
	var_name = (char *)malloc((i * sizeof(char)) + 1);
	if (!var_name)
		return (NULL);
	i = 0;
	while (token[i] && !cst(token[i])
		&& !is_expand_exception(token[i]))
	{
		var_name[i] = token[i];
		if (token[i + 1] && token[i] == '\'' && token[i + 1] == '\"')
			break ;
		i++;
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
		if (ft_strncmp(var_name, (char *)tmp->content,
				ft_strlen(var_name)) == 0)
			expanded_name = fill_expanded_name((char *)tmp->content, i + 1);
		tmp = tmp->next;
	}
	if (!expanded_name)
	{
		free(expanded_name);
		expanded_name = NULL;
		expanded_name = (char *)ft_calloc(1, 1);
	}
	return (expanded_name);
}

char	*get_prestring(char	*token)
{
	int		i;
	char	*pre;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && is_not_between_squotes(token, i))
			break ;
		i++;
	}
	pre = (char *)malloc(i * sizeof(char) + 1);
	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && is_not_between_squotes(token, i))
			break ;
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

	i = count_poststring(token);
	i++;
	while (token[i] && !cst(token[i]) && !is_expand_exception(token[i]))
	{
		if (token[i] == '\'' && token[i + 1] == '\"')
			break ;
		i++;
	}
	len = 0;
	while (token[i++])
		len++;
	post = (char *)malloc(len * sizeof(char) + 1);
	if (!post)
		return (NULL);
	j = 0;
	i = i - len - 1;
	while (j < len)
		post[j++] = token[i++];
	post[j] = '\0';
	return (post);
}
