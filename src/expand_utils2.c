/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:10:03 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/13 17:11:26 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_expand_exception(char c)
{
	if (c == '/' || c == '=' || c == '\"' || c == '$'
		|| c == '\\' || c == '\'' || c == '+' || c == '-')
		return (1);
	return (0);
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
