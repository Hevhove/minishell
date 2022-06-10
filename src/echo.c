/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:29:47 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/10 11:53:49 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exec_echo(char **tokens)
{
	int		i;

	if (!tokens[1])
	{
		ft_printf("\n");
		return (0);
	}
	i = 1;
	while (ft_strncmp(tokens[i], "-n", 2) == 0)
		i++;
	while (tokens[i])
	{
		ft_printf("%s", tokens[i]);
		if (tokens[i][0] != '\0' && tokens[i + 1])
			ft_printf(" ");
		i++;
	}
	if (ft_strncmp(tokens[1], "-n", 2) != 0)
		ft_printf("\n");
	return (0);
}
