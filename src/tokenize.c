/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 18:59:31 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/07 18:06:50 by hvan-hov         ###   ########.fr       */
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
		if (s[i] == '\0')
			return (0);
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

void	token_alloc(char **tokens, int wc, int word_len)
{
	tokens[wc] = (char *)malloc((word_len + 1) * sizeof(char));
	if (!tokens[wc])
		exit(3);
	return ;
}

void	add_tokens(char **tokens, const char *s, int wc, int i)
{
	int	w_l;

	while (s[i])
	{
		if (s[i] == CHAR_WHITESPACE)
			i++;
		else
		{
			w_l = 0;
			if (check_token_type(s[i]) == 1)
				w_l = w_l + metachar_wordlen(s, i);
			else
			{
				while (s[i + w_l] != CHAR_WHITESPACE
					&& check_token_type(s[i + w_l]) != 1 && s[i + w_l])
				{
					w_l = w_l + check_quotes(s + i) + 1;
					w_l = w_l + postcheck(s + i + w_l);
				}
			}
			token_alloc(tokens, wc, w_l);
			i += write_token(tokens[wc++], s + i, w_l);
		}
	}
}

char	**tokenize(const char *s)
{
	char	**tokens;
	int		wc;
	int		wc2;
	int		i2;

	if (!s)
		return (NULL);
	wc = word_count(s);
	if (wc < 1)
		return (NULL);
	printf("wc is :%d\n", wc);
	tokens = (char **)malloc((wc + 1) * sizeof(tokens));
	if (!tokens)
		return (NULL);
	wc2 = 0;
	i2 = 0;
	add_tokens(tokens, s, wc2, i2);
	tokens[wc] = NULL;
	return (tokens);
}
