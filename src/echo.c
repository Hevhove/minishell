/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:29:47 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/05/23 19:30:09 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exec_echo(char **tokens)
{
	int	i;

	if (!tokens[1])
	{
		printf("\n");
		return ;
	}
	i = 1;
	if (ft_strcmp(tokens[1], "-n") == 0)
		i = 2;
	while (tokens[i])
	{
		printf("%s", tokens[i]);
		if (tokens[i + 1])
			printf(" ");
		i++;
	}
	if (ft_strcmp(tokens[1], "-n") != 0)
		printf("\n");
}