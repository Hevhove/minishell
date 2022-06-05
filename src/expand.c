/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:39:55 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/05 12:02:13 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	Quote Checking Function:
|	This function checks whether or not the outer quotes around the dollar sign
|	are single or double quotes.
|	In case of dquotes we need to expand, in case of single quotes we do not
*/

int	st_end_qts(char *token, int i, int dollar_count)
{
	while (token[i])
	{
		if (token[i] == '\'')
		{
			while (token[i++])
			{
				if (token[i] == '$')
					dollar_count = 1;
				if (token[i] == '\'' && dollar_count == 1)
					return (1);
			}
		}
		if (token[i] == '\"')
		{
			while (token[i++])
			{
				if (token[i] == '$')
					dollar_count = 1;
				if (token[i] == '\"' && dollar_count == 1)
					return (2);
			}
		}
		i++;
	}
	return (0);
}

// void	text_replace(char **token, int len, char *str)
// {
// 	char	*pre;
// 	char	*inter;
// 	int		i;

// 	i = 0;
// 	pre = (char *)malloc(sizeof(char) * (len + 1));
// 	ft_strlcpy(pre, *token, len);
// 	free(*token);
// 	*token = NULL;
// 	*token = ft_strjoin(pre, str);
// 	if (pre[0] == '\"')
// 	{
// 		inter = ft_strjoin(*token, "\"");
// 		free(*token);
// 		*token = inter;
// 	}
// 	free(pre);
// 	return ;
// }

/*	Expand Tokens function:
|	This function expands the $ for variables, and handles the following cases:
|	CASE1: $PWD			-> WORKS
|	CASE2: "$PWD"		-> WORKS
|	CASE3: $PWDo		-> Variable doesn't exist and will remain as $PWDo for now
|	CASE4: "old$PWD"	-> WORKS. Variable will be expanded with the prefix
|	CASE5: "$PWD"old	-> WORKS
|
|	INPUT:	tokens[0] is: echo
|			tokens[1] is: "old$PWD"
|
|	OUTPUT:
|			tokens[0] is: echo
|			tokens[1] is: "old/Users/hvan-hov/Documents/minishell"
*/

// void	expand_tokens(char **tokens)
// {
// 	int		i;
// 	int		j;
// 	char	*tmp;
// 	char	*str;

// 	i = 0;
// 	while (tokens[i]) // start_end_quote(tokens[i]) != 1 &&
// 	{ // write a function that checks if dollar sign is between double quotes
// 		if (ft_strchr(tokens[i], '$')) // "$PWD"lol expansion also needs
//		to work if token-end is not a quote
// 		{
// 			j = 0;
// 			while (tokens[i][j] != '$' && tokens[i][j])
// 				j++;
// 			tmp = ft_strtrim(tokens[i] + j + 1, " \""); // $PWDlol
// 			printf("PWDvar is: %s\n", tmp);
// 			str = getenv(tmp); // fix this
// 			free(tmp);
// 			if (!str)
// 				break ;
// 			text_replace(&tokens[i], j + 1, str);
// 		}
// 		i++;
// 	}
// }

char	*replace_token(char	*token, char *exp_name)
{
	char	*pre;
	char	*post;
	char	*result;
	char	*result2;
	int		i;

	i = 0;
	pre = get_prestring(token);
	post = get_poststring(token);
	result = ft_strjoin(pre, exp_name);
	free(pre);
	free(exp_name);
	result2 = ft_strjoin(result, post);
	free(result);
	free(post);
	return (result2);
}

char	*dollar_expansion(char *orig, char	*token, t_list **env)
{
	char	*var_name;
	char	*expanded_name;
	char	*new_token;

	var_name = get_var_name(token);
	if (ft_strncmp(var_name, "?", 1) == 0)
		expanded_name = ft_itoa(cmd.exit_status);
	else
		expanded_name = get_expanded_name(var_name, env);
	new_token = replace_token(orig, expanded_name);
	free(var_name);
	return (new_token);
}

int	is_exit_code(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i + 1] && token[i] == '$' && token[i + 1] == '?')
			return (1);
		i++;
	}
	return (0);
}

void	expand_tokens(char	**tokens, t_list **env)
{
	int		i;
	int		j;
	int		i2;
	int		j2;
	char	*new_token;

	i2 = 0;
	j2 = 0;
	i = 0;
	while (tokens[i])
	{
		if (ft_strchr(tokens[i], '$') && st_end_qts(tokens[i], i2, j2) != 1)
		{
			j = 0;
			while (tokens[i][j] && tokens[i][j] != '$')
				j++;
			new_token = dollar_expansion(tokens[i], tokens[i] + j + 1, env);
			free(tokens[i]);
			tokens[i] = new_token;
		}
		i++;
	}
}
