/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:39:55 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/10 12:37:32 by hvan-hov         ###   ########.fr       */
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
	post = get_poststring(token);
	result = ft_strjoin(pre, exp_name);
	free(pre);
	free(exp_name);
	result2 = ft_strjoin(result, post);
	free(result);
	free(post);
	return (result2);
}

char	*remove_var(char	*token, char	*var_name)
{
	int		pos;
	int		i;
	int		j;
	char	*new_token;

	new_token = (char *)malloc((ft_strlen(token)
				- (ft_strlen(var_name)) * sizeof(char)) + 21);
	pos = 0;
	while (ft_strncmp(token + pos, var_name, ft_strlen(var_name)) != 0)
		pos++;
	i = 0;
	j = 0;
	while (token[i])
	{
		if (i == pos - 1)
			i += ft_strlen(var_name) + 1;
		new_token[j] = token[i];
		i++;
		j++;
	}
	new_token[j] = '\0';
	return (new_token);
}

char	*expand_exit_val(char *orig)
{
	char	*new_token;
	int		i;
	int		j;
	
	new_token = (char *)malloc(ft_strlen(orig));
	i = 0;
	j = 0;
	while (orig[i])
	{
		if (orig[i] && orig[i] != '$')
			new_token[j++] = orig[i++];
		else if (orig[i] == '$' && is_not_between_squotes(orig, i))
		{
			new_token[j++] = *ft_itoa(g_cmd.exit_status);
			if (orig[i] && orig[i + 1] != '\0')
				i++;
		}
		i++;
	}
	new_token[j] = '\0';
	return (new_token);
}

char	*dollar_expansion(char *orig, char	*token, t_list **env)
{
	char	*var_name;
	char	*expanded_name;
	char	*new_token;

	var_name = get_var_name(token);
	if (ft_strcmp(var_name, "?") == 0)
		expanded_name = ft_itoa(g_cmd.exit_status); // TO FIX THIS FUNCTION
	else
		expanded_name = get_expanded_name(var_name, env);
	if (expanded_name[0] == '\0')
		new_token = remove_var(orig, var_name);
	else
	{
		new_token = replace_token(orig, expanded_name);
	}
	if (var_name)
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

/*
|	ATTENTION: if the variable is not found (Such as $PWDlol), then the new
|	token will be '\0'.
|	Echo must then deal with this appropriately.
*/

int	is_not_between_squotes(char	*token, int i)
{
	int	j;
	int	left;
	int	right;

	j = i;
	left = 0;
	right = 0;
	while (i-- >= 0)
	{
		if (token[i] == '\'')
			left = 1;
	}
	while (token[j++])
	{
		if (token[j] == '\'')
			right = 1;
	}
	if (right && left)
		return (0);
	return (1);
}

int	dollar_remaining(char	*token)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (token[i])
	{
		if (token[i] == '$')
			check += is_not_between_squotes(token, i);
		i++;
	}
	if (check > 0)
		return (1);
	else
		return (0);
}

int	find_first_expansion(char	*token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && is_not_between_squotes(token, i))
			return (i);
		i++;
	}
	return (-1);
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
		if (find_first_expansion(tokens[i]) != -1)
		{
			if (ft_strchr(tokens[i], '$')[1] == '\0' || check_spacetab(ft_strchr(tokens[i], '$')[1]) || is_expand_exception(ft_strchr(tokens[i], '$')[1]))
			{
				i++;
				continue ;
			}
			j = find_first_expansion(tokens[i]);
			new_token = dollar_expansion(tokens[i], tokens[i] + j + 1, env);
			free(tokens[i]);
			tokens[i] = NULL;
			tokens[i] = new_token;
		}
		if (dollar_remaining(tokens[i]))
			continue ;
		i++;
	}
	handle_quotes(tokens);
}
