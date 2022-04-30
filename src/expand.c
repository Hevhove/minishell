/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:39:55 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/04/30 13:01:46 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	start_end_quote(char *token)
{
	int	i;

	i = 0;
	if (token[i++] == '\'')
	{
		while (token[i])
		{
			if (token[i] == '\'')
				return (1);
			i++;
		}
	}
	i = 0;
	if (token[i++] == '\"')
	{
		while (token[i])
		{
			if (token[i] == '\"')
				return (2);
			i++;
		}
	}
	return (0);
}

void	text_replace(char **token, int len, char *str)
{
	char	*pre;
	char	*inter;
	int		i;

	i = 0;
	pre = (char *)malloc(sizeof(char) * (len + 1));
	ft_strlcpy(pre, *token, len);
	printf("pre is: %s\n", pre);
	free(*token);
	*token = NULL;
	*token = ft_strjoin(pre, str);
	printf("INSIDE is: %s\n", *token);
	if (pre[0] == '\"')
	{
		inter = ft_strjoin(*token, "\"");
		free(*token);
		*token = inter;
	}
	free(pre);
	return ;
}

/*	Expand Tokens function:
|	This function expands the $ for variables, and handles the following cases:
|	CASE1: $PWD			-> WORKS
|	CASE2: "$PWD"		-> WORKS
|	CASE3: $PWDo		-> Variable doesn't exist and will remain as $PWDo for now
|	CASE4: "old$PWD"	-> WORKS. Variable will be expanded with the prefix
|	
|	INPUT:	tokens[0] is: echo
|			tokens[1] is: "old$PWD"
|
|	OUTPUT: 
|			tokens[0] is: echo
|			tokens[1] is: "old/Users/hvan-hov/Documents/minishell"
*/

void	expand_tokens(char **tokens)
{
	int		i;
	int		j;
	char	*str;
	char	*pretext;

	i = 0;
	while (tokens[i])
	{
		if (start_end_quote(tokens[i]) != 1 && ft_strchr(tokens[i], '$'))
		{
			j = 0;
			pretext = (char *)malloc((j + 1) * sizeof(char));
			while (tokens[i][j] != '$' && tokens[i][j])
				j++;
			str = getenv(ft_strtrim(tokens[i] + j + 1, " \""));
			if (!str)
				break ;
			text_replace(&tokens[i], j + 1, str);
		}
		i++;
	}
}
