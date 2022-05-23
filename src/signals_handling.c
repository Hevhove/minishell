/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 17:40:11 by mmaxime-          #+#    #+#             */
/*   Updated: 2022/05/23 17:08:46 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// void	handle_signals(int sig)
// {
// 	if (sig == SIGQUIT)
// 		printf("exit\n");
// 	else if (sig == SIGINT)
// 	{
// 		printf("\n");
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
	
// }

// void	exec_signals(void)
// {
// 	struct sigaction	sa;

// 	sa.sa_handler = &handle_signals;
// 	sigaction(SIGQUIT, &sa, NULL);
// 	sigaction(SIGINT, &sa, NULL);
// }