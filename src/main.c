/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hendrik <Hendrik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:39:27 by Hendrik           #+#    #+#             */
/*   Updated: 2022/04/11 18:03:19 by Hendrik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include "../inc/minishell.h"
#include <stdlib.h>

static char *line_read = (char *)NULL; // many programs seem to be having the line as the global var

int	main(void)
{
	line_read = readline("42sh$ ");
	while (strncmp(line_read, "exit", 4) != 0)
	{
		printf("the entered string was: %s\n", line_read);
		if (line_read && *line_read)
			add_history(line_read);
		free(line_read);
		line_read = readline("42sh$ ");
	}
	printf("exiting shell\n");
	// printf("the entered string was: %s\n", str1);
	return (0);
}
