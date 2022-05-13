/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 18:59:31 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/05/13 19:45:31 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	word_count(const char *s)
{
	int	wc;
	int	i;

	i = 0;
	wc = 0;
	while (s[i])
	{
		while (s[i] == CHAR_WHITESPACE)
			i++;
		if (metachar_wordlen(s, i) != 0)
		{
			i = i + metachar_wordlen(s, i) + 1;
			wc++;
			continue ;
		}
		while (s[i] && s[i] != CHAR_WHITESPACE && check_token_type(s[i]) != 1)
			i = i + check_quotes(s + i) + 1;
		wc++;
		if (s[i] == CHAR_WHITESPACE)
			i++;
	}
	return (wc);
}

static int	write_token(char *dst, const char *src, int word_len)
{
	int	i;

	i = 0;
	while (i < word_len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (word_len);
}

static int	add_tokens(char **tokens, const char *s)
{
	int	i;
	int	word_len;
	int	wc;

	i = 0;
	wc = 0;
	while (s[i])
	{
		if (s[i] == CHAR_WHITESPACE)
			i++;
		else
		{
			word_len = 0;
			if (check_token_type(s[i]) == 1)
				word_len = word_len + metachar_wordlen(s, i);
			else
			{
				while (s[i + word_len] != CHAR_WHITESPACE
					&& check_token_type(s[i + word_len]) != 1 && s[i + word_len])
					word_len = word_len + check_quotes(s + i) + 1;
			}
			tokens[wc] = (char *)malloc((word_len + 1) * sizeof(char));
			if (!tokens[wc])
				return (-1);
			i += write_token(tokens[wc++], s + i, word_len);
		}
	}
	return (0);
}

char	**tokenize(const char *s)
{
	char	**tokens;
	int		wc;

	if (!s)
		return (NULL);
	wc = word_count(s);
	tokens = (char **)malloc((wc + 1) * sizeof(tokens));
	if (!tokens)
		return (NULL);
	if (add_tokens(tokens, s) == -1)
		return (NULL);
	tokens[wc] = NULL;
	return (tokens);
}

// void	free_tokens(char **tokens)
// {
// 	int	i;

// 	i = 0;
// 	while (tokens[i])
// 	{
// 		free(tokens[i]);
// 		i++;
// 	}
// 	free(tokens);
// }
