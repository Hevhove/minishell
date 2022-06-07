/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 17:40:11 by mmaxime-          #+#    #+#             */
/*   Updated: 2022/06/07 20:58:21 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	handle_signals(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_cmd.exit_status = 1;
	}
	return ;
}

static void	handle_signals_child(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("^C\n");
		g_cmd.exit_status = 130;
	}
	if (sig == SIGQUIT)
	{
		ft_printf("^\\Quit: 3\n");
		g_cmd.exit_status = 131;
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
			exit (-1);
		if (sigaction(SIGQUIT, &sa, NULL) < 0)
			exit (-1);
	}
	else
	{
		sa.sa_handler = &handle_signals;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		if (sigaction(SIGINT, &sa, NULL) < 0)
			exit (-1);
		if (signal(SIGQUIT, SIG_IGN) < 0)
			exit (-1);
	}
}
