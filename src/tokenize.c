/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 18:59:31 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/05/02 15:06:40 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../inc/minishell.h"

// static int	check_quotes(const char *s)
// {
// 	int	i;

// 	i = 0;
// 	if (s[i] == '\"')
// 	{
// 		i++;
// 		while (s[i] != '\"' && s[i])
// 			i++;
// 	}
// 	if (s[i] == '\'')
// 	{
// 		i++;
// 		while (s[i] != '\'' && s[i])
// 			i++;
// 	}
// 	return (i);
// }

// static int	word_count(const char *s, char c)
// {
// 	int	wc;
// 	int	i;

// 	i = 0;
// 	wc = 0;
// 	while (s[i])
// 	{
// 		while (s[i] == c)
// 			i++;
// 		while (s[i] && s[i] != c)
// 			i = i + check_quotes(s + i) + 1;
// 		wc++;
// 		if (s[i])
// 			i++;
// 	}
// 	return (wc);
// }

// static void	write_token(char *dst, const char *src, int word_len)
// {
// 	int	i;

// 	i = 0;
// 	while (i < word_len)
// 	{
// 		dst[i] = src[i];
// 		i++;
// 	}
// 	dst[i] = '\0';
// }

// static int	add_tokens(char **tokens, const char *s, char c)
// {
// 	int	i;
// 	int	word_len;
// 	int	wc;

// 	i = 0;
// 	wc = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == c)
// 			i++;
// 		else
// 		{
// 			word_len = 0;
// 			while (s[i + word_len] != c && s[i + word_len])
// 				word_len = word_len + check_quotes(s + i) + 1;
// 			tokens[wc] = malloc((word_len + 1) * sizeof(char));
// 			if (!tokens[wc])
// 				return (-1);
// 			write_token(tokens[wc], s + i, word_len);
// 			i += word_len;
// 			wc++;
// 		}
// 	}
// 	return (0);
// }

// void	print_tokens(char **tokens)
// {
// 	int	i;

// 	i = 0;
// 	if (!tokens)
// 		exit(1);
// 	printf("#----#\n");
// 	while (tokens[i])
// 	{
// 		printf("tokens[%d] is: %s\n", i, tokens[i]);
// 		i++;
// 	}
// 	printf("#----#\n");
// 	return ;
// }

// char	**tokenize(const char *s)
// {
// 	char	**tokens;
// 	int		wc;

// 	if (!s)
// 		return (NULL);
// 	wc = word_count(s, ' ');
// 	tokens = (char **)malloc((wc + 1) * sizeof(tokens));
// 	if (!tokens)
// 		return (NULL);
// 	if (add_tokens(tokens, s, ' ') == -1)
// 		return (NULL);
// 	tokens[wc] = NULL;
// 	return (tokens);
// }

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
