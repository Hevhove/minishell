/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:46:58 by mmaxime-          #+#    #+#             */
/*   Updated: 2022/06/07 11:19:40 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_term(void)
{
	struct termios	term;

	if (tcgetattr(0, &term) != 0)
	{
		perror("error in tcgetattr");
		return ;
	}
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, TCSANOW, &term) != 0)
	{
		perror("error in tcsetattr");
		return ;
	}
}
