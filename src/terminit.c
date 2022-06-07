/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:46:58 by mmaxime-          #+#    #+#             */
/*   Updated: 2022/06/07 12:49:01 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	init_term(void)
{
	struct termios	term;

	if (tcgetattr(0, &term) != 0)
	{
		ft_putstr_fd("error in tcgetattr", STDERR_FILENO);
		return (-1);
	}
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, TCSANOW, &term) != 0)
	{
		ft_putstr_fd("error in tcsetattr", STDERR_FILENO);
		return (-1);
	}
	return (0);
}
