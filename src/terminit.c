/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:46:58 by mmaxime-          #+#    #+#             */
/*   Updated: 2022/05/22 17:30:37 by mmaxime-         ###   ########.fr       */
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
	term.c_lflag &= ~ECHOCTL; // in order to turn off ECHO, so whatever we type is not printed twice on the terminal
	if (tcsetattr(0, TCSANOW, &term) != 0);
	{
		perror("error in tcsetattr");
		return ;
	}
}