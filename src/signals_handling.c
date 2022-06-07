/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 17:40:11 by mmaxime-          #+#    #+#             */
/*   Updated: 2022/06/07 11:56:01 by mmaxime-         ###   ########.fr       */
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
		cmd.exit_status = 1;
	}
	return ;
}

static void	handle_signals_child(int sig)
{
	if (sig == SIGINT)
	{
		printf("^C\n");
		cmd.exit_status = 130;
	}
	if (sig == SIGQUIT)
	{
		printf("^\\Quit: 3\n");
		cmd.exit_status = 131;
	}
	return ;
}

void	exec_signals(t_status status)
{
	struct sigaction	sa;

	if (status == CHILD_PROCESS)
	{
		sa.sa_handler = &handle_signals_child;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		if (sigaction(SIGINT, &sa, NULL) < 0)
			return ; // check how to set a specific error code (maybe a function)
		if (sigaction(SIGQUIT, &sa, NULL) < 0)
			return ; // check how to set a specific error code (maybe a function)
	}
	else
	{
		sa.sa_handler = &handle_signals;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		if (sigaction(SIGINT, &sa, NULL) < 0)
			return ;
		if (signal(SIGQUIT, SIG_IGN) < 0)
			return ;
	}
}
