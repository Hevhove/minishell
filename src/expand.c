/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:39:55 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/05 19:09:11 by hvan-hov         ###   ########.fr       */
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

char	*replace_token(char	*token, char *exp_name)
{
	char	*pre;
	char	*post;
	char	*result;
	char	*result2;
	int		i;

	i = 0;
	pre = get_prestring(token);
	printf("prestring is: %s\n", pre);
	post = get_poststring(token);
	printf("poststring is: %s\n", post);
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
	printf("var_name is %s\n", var_name);
	if (ft_strncmp(var_name, "?", 1) == 0)
		expanded_name = ft_itoa(cmd.exit_status);
	else
		expanded_name = get_expanded_name(var_name, env);
	if (expanded_name[0] == '\0')
		return (expanded_name);
	printf("expanded_name is: %s\n", expanded_name);
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
			tokens[i] = remove_outer_quotes(tokens[i]);
			free(tmp);
			printf("tokens[%d] is: %s\n", i, tokens[i]);
		}
		i++;
	}
}

/*
|	ATTENTION: if the variable is not found (Such as $PWDlol), then the new token will be '\0'.
|	Echo must then deal with this appropriately.
*/

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
			tokens[i] = new_token;
		}
		i++;
	}
	handle_quotes(tokens);
}
