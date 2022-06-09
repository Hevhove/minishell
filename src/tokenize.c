/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 18:59:31 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/09 18:30:45 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	line_empty(const char *s)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (s[i] && check_spacetab(s[i]))
		i++;
	if (i == (int)ft_strlen(s))
		return (1);
	return (0);
}

int	check_spacetab(char c)
{
	if (c == CHAR_WHITESPACE)
		return (1);
	else if (c == CHAR_TAB)
		return (1);
	else
		return (0);
}

static int	word_count(const char *s)
{
	int	wc;
	int	i;

	i = 0;
	wc = 0;
	if (line_empty(s))
		return (0);
	while (s[i])
	{
		while (check_spacetab(s[i]))
			i++;
		if (s[i] == '\0')
			return (wc);
		if (metachar_wordlen(s, i) != 0)
		{
			i = i + metachar_wordlen(s, i) + 1;
			wc++;
			continue ;
		}
		while (s[i] && !check_spacetab(s[i]) && check_token_type(s[i]) != 1)
			i = i + check_quotes(s + i) + 1;
		wc++;
		if (check_spacetab(s[i]))
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

int	token_alloc(char **tokens, int wc, int word_len)
{
	tokens[wc] = (char *)malloc((word_len + 1) * sizeof(char));
	if (!tokens[wc])
	{
		ft_putstr_fd("error: malloc failed\n", 2);
		return (-1);
	}
	return (0);
}

int	add_tokens(char **tokens, const char *s, int wc, int i)
{
	int	w_l;
	int	ret;

	while (s[i])
	{
		if (check_spacetab(s[i]))
			i++;
		else
		{
			w_l = 0;
			if (check_token_type(s[i]) == 1)
				w_l = w_l + metachar_wordlen(s, i);
			else
			{
				while (!check_spacetab(s[i + w_l])
					&& check_token_type(s[i + w_l]) != 1 && s[i + w_l])
				{
					w_l = w_l + check_quotes(s + i) + 1;
					w_l = w_l + postcheck(s + i + w_l);
				}
			}
			ret = token_alloc(tokens, wc, w_l);
			i += write_token(tokens[wc++], s + i, w_l);
		}
	}
	return (ret);
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
	tokens = (char **)malloc((wc + 1) * sizeof(tokens));
	if (!tokens)
		return (NULL);
	wc2 = 0;
	i2 = 0;
	if (add_tokens(tokens, s, wc2, i2) < 0)
		return (NULL);
	tokens[wc] = NULL;
	return (tokens);
}
