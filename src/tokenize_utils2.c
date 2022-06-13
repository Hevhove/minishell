/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:52:04 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/13 18:05:11 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	line_empty(const char *s)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (s[i] && cst(s[i]))
		i++;
	if (i == (int)ft_strlen(s))
		return (1);
	return (0);
}

int	cst(char c)
{
	if (c == CHAR_WHITESPACE)
		return (1);
	else if (c == CHAR_TAB)
		return (1);
	else
		return (0);
}
