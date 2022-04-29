/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:39:55 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/04/29 18:24:50 by hvan-hov         ###   ########.fr       */
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

char *strip_quote(char *str)
{
	int	i;
	char *stripped;

	if (str[ft_strlen(str) - 1] == '\"')
	{
		stripped = (char *)malloc(sizeof(char) * (ft_strlen(str)));
		if (!stripped)
			return (NULL);
		i = 0;
		while (i < (int)ft_strlen(str) - 1)
		{
			stripped[i] = str[i];
			i++;
		}
		stripped[i] = '\0';
		printf("stripped string: %s\n", stripped);
		return (stripped);
	}
	return (str);
}

void	expand_tokens(char **tokens, char **envp) // echo "hello $PWD"
{
	int		i;
	int		j;
	char	*str;
	char	*pretext;
	// case1: $PWD
	// case2: "$PWD"
	// case3: $PWDo
	// case4: "old$PWD"

	(void)envp;
	i = 0;
	while (tokens[i])
	{
		if (start_end_quote(tokens[i]) == 1)
			i++;
		else
		{
			j = 0;
			pretext = (char *)malloc((j + 1) * sizeof(char));
			while (tokens[i][j] != '$' && tokens[i][j])
			{
				if (tokens[i][j] == '\"')
				{
					pretext[j] = tokens[i][j];
					j++;
					pretext[j] = '\0';
				}
				j++;
			}
			str = getenv(ft_strtrim(tokens[i] + j + 1, " \""));
			printf("str is : %s\n", str);
			free(tokens[i]);
			printf("PRETEXT IS: %s\n", pretext);
			tokens[i] = ft_strjoin(pretext, str);
			if (!tokens[i])
				// exit?
			// len = ft_strlen(str);
			free(pretext);
			printf("does this happen?\n");
		}
		i++;
		// printf("check\n");
	}
}

// int main(void)
// {
// 	char str[] = "lol baby  $PWD";

// 	printf("result is: %d\n", check_single_literal(str));
// 	return (0);
// }
