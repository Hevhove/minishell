/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:29:47 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/07 20:58:10 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exec_echo(char **tokens)
{
	int	i;

	if (!tokens[1])
	{
		ft_printf("\n");
		return (0);
	}
	i = 1;
	if (ft_strcmp(tokens[1], "-n") == 0)
		i = 2;
	while (tokens[i])
	{
		ft_printf("%s", tokens[i]);
		if (tokens[i][0] != '\0' && tokens[i + 1])
			ft_printf(" ");
		i++;
	}
	if (ft_strcmp(tokens[1], "-n") != 0)
		ft_printf("\n");
	return (0);
}
