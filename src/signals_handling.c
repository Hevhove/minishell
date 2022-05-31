/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miam <miam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 17:40:11 by mmaxime-          #+#    #+#             */
/*   Updated: 2022/05/31 17:41:40 by miam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	handle_signals(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return ;
}

static void	handle_signals_child(int sig)
{
	if (sig == SIGINT)
		printf("^C\n"); // should add an exit code
	if (sig == SIGQUIT)
		printf("^\\Quit: 3\n"); // should add an exit code
	return ;
}

void	exec_signals(t_status status)
{
	struct sigaction	sa;

	if (status == CHILD_PROCESS) // when exec_signals is launched in a child process
	{
		sa.sa_handler = &handle_signals_child;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		if (sigaction(SIGINT, &sa, NULL) < 0)
			return ; // check how to set a specific error code (maybe a function)
		if (sigaction(SIGQUIT, &sa, NULL) < 0)
			return ; // check how to set a specific error code (maybe a function)
	}
	else // for other status (INIT or RESET)
	{
		sa.sa_handler = &handle_signals;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sigaction(SIGQUIT, &sa, NULL); // to check how to set SIGQUIT as SIGIGN
		sigaction(SIGINT, &sa, NULL);
	}
}