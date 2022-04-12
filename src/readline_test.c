/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:06:18 by mmaxime-          #+#    #+#             */
/*   Updated: 2022/04/12 15:06:22 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

static char	*line_read = (char *)NULL; // a static variable for holding the line.



char	*rl_gets() // read a string and return a pointer to it. Returns NULL on EOF.
{
	if (line_read) // if the buffer has already been allocated, return the memory to the free pool.
	{
		free(line_read);
		line_read = (char *)NULL;
	}
	line_read = readline("Enter a line: \n"); // in order to be able to compile, we have to add -lreadline flag to gcc
	if (line_read && *line_read) // if the line has any text in it, save it on the history
		add_history(line_read);
	return (0);
}