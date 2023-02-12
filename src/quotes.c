/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 12:20:05 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/07 21:52:05 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*remove_outer_quotes(char *token)
{
	int		i;
	int		j;
	char	*new_token;

	new_token = (char *)malloc(ft_strlen(token) * sizeof(char));
	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i] == '\'' || token[i] == '\"')
		{
			i++;
			continue ;
		}
		new_token[j] = token[i];
		j++;
		i++;
	}
	new_token[j] = '\0';
	return (new_token);
}

char	*remove_first_quote(char *token)
{
	int		i;
	int		j;
	int		check;
	char	*new_token;

	i = 0;
	j = 0;
	check = 0;
	new_token = (char *)malloc(ft_strlen(token) * sizeof(char));
	while (token[i])
	{
		if (check == 0 && (token[i] == '\"' || token[i] == '\''))
		{
			i++;
			check = 1;
		}
		new_token[j] = token[i];
		i++;
		j++;
	}
	new_token[j] = '\0';
	return (new_token);
}

char	*remove_last_quote(char *token)
{
	int		i;
	int		j;
	int		check;
	char	*new_token;

	i = ft_strlen(token) - 1;
	check = 0;
	new_token = (char *)malloc(ft_strlen(token) * sizeof(char) + 1);
	while (i > 0)
	{
		if (check == 0 && (token[i] == '\"' || token[i] == '\''))
			check = i;
		i--;
	}
	j = 0;
	while (i < (int)(ft_strlen(token)))
	{
		if (i == check)
			i++;
		new_token[j] = token[i];
		j++;
		i++;
	}
	new_token[j] = '\0';
	return (new_token);
}

/*
|	We could go much further into depth in this function, but for efficiency's sake
|	we decided to just remove the outer quotes and ignore the inside quotes
|	We do this by stepwise removing the first and last quote.
*/

void	handle_quotes(char **tokens)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tokens[i])
	{
		if (ft_strchr(tokens[i], '\"') || ft_strchr(tokens[i], '\''))
		{
			tmp = tokens[i];
			tokens[i] = remove_first_quote(tokens[i]);
			free(tmp);
			tmp = NULL;
			tmp = tokens[i];
			tokens[i] = remove_last_quote(tokens[i]);
			free(tmp);
		}
		i++;
	}
}
