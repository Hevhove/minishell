/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:51:15 by Hendrik           #+#    #+#             */
/*   Updated: 2022/06/13 18:13:15 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	ft_printf("#----#\n");
	while (tokens[i])
	{
		ft_printf("tokens[%d] is: %s\n", i, tokens[i]);
		i++;
	}
	ft_printf("#----#\n");
	return ;
}

int	ctt(int token)
{
	if (token == CHAR_PIPE
		|| token == CHAR_AMPERSAND
		|| token == CHAR_GREATER
		|| token == CHAR_LESSER)
		return (1);
	else if (token == CHAR_SQUOTE
		|| token == CHAR_DQUOTE)
		return (2);
	return (0);
}

int	check_quotes(const char *s)
{
	int	i;

	i = 0;
	if (s[i] == CHAR_DQUOTE)
	{
		i++;
		while (s[i] != CHAR_DQUOTE && s[i])
			i++;
	}
	else if (s[i] == CHAR_SQUOTE)
	{
		i++;
		while (s[i] != CHAR_SQUOTE && s[i])
			i++;
	}
	return (i);
}

int	metachar_wordlen(const char *s, int offset)
{
	if (*(s + offset) == CHAR_PIPE || *(s + offset) == CHAR_AMPERSAND)
		return (0);
	if (offset < (int)ft_strlen(s))
	{
		if (*(s + offset) == CHAR_GREATER && *(s + offset + 1) == CHAR_GREATER)
			return (1);
		else if (*(s + offset) == CHAR_LESSER
			&& *(s + offset + 1) == CHAR_LESSER)
			return (1);
		else if (*(s + offset) == CHAR_GREATER || *(s + offset) == CHAR_LESSER)
			return (0);
	}
	return (-1);
}

int	postcheck(const char *token)
{
	int	i;

	i = 0;
	while (token[i] && ctt(token[i]) != 1
		&& !cst(token[i]))
		i++;
	return (i);
}
