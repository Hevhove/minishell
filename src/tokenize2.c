/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hendrik <Hendrik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 18:59:31 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/05/03 13:04:08 by Hendrik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_token_type(int token)
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

static int	check_quotes(const char *s)
{
	int	i;

	i = 0;
	if (s[i] == CHAR_DQUOTE)
	{
		i++;
		while (s[i] != CHAR_DQUOTE && s[i])
			i++;
	}
	if (s[i] == CHAR_SQUOTE)
	{
		i++;
		while (s[i] != CHAR_SQUOTE && s[i])
			i++;
	}
	return (i);
}

int metachar_wordlen(const char *s, int offset)
{
	if (*(s + offset) == CHAR_PIPE || *(s + offset) == CHAR_AMPERSAND)
		return (1);
	if (offset < (int)ft_strlen(s))
	{
		if (*(s + offset) == CHAR_GREATER && *(s + offset + 1) == CHAR_GREATER)
			return (2);
		else if (*(s + offset) == CHAR_LESSER && *(s + offset + 1) == CHAR_LESSER)
			return (2);
		else if (*(s + offset) == CHAR_GREATER || *(s + offset) == CHAR_LESSER)
			return (1);
	}
	return (0);
}

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

static int	add_tokens(char **tokens, const char *s) // echo "hello $PWD"|wc -l>>outfile
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
				while (s[i + word_len] != CHAR_WHITESPACE && check_token_type(s[i + word_len]) != 1 && s[i + word_len])
					word_len = word_len + check_quotes(s + i) + 1;
			}
				tokens[wc] = (char *)malloc((word_len + 1) * sizeof(char));
				i += write_token(tokens[wc++], s + i, word_len);
		}
	}
	return (0);
}

void	print_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		exit(1);
	printf("#----#\n");
	while (tokens[i])
	{
		printf("tokens[%d] is: %s\n", i, tokens[i]);
		i++;
	}
	printf("#----#\n");
	return ;
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
//
// int main(void)
// {
// 	char 	str1[] = "     hello test    here";
// 	char 	str2[] = "Hello     there      \" this is a test baby\" and more";
// 	int		i;
// 	char	**tokens;
//
// 	tokens = tokenize(str2, ' ');
// 	i = 0;
// 	while (tokens[i])
// 	{
// 		printf("content %d is: %s\n", i, tokens[i]);
// 		i++;
// 	}
// 	free_tokens(tokens);
// 	return (0);
// }
