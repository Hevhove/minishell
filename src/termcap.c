/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:46:58 by mmaxime-          #+#    #+#             */
/*   Updated: 2022/05/20 13:07:38 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <ncurses.h>
#include <term.h>

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	
	char	*term_type;
	int		ret;

	term_type = getenv("TERM");
	ret = tgetent(NULL, term_type);

	return (ret);
}