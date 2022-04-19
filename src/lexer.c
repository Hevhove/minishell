/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:00:52 by mmaxime-          #+#    #+#             */
/*   Updated: 2022/04/19 17:54:01 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*rl_gets(char *line_read) // read a string and return a pointer to it. Returns NULL on EOF.
{
	if (line_read) // if the buffer has already been allocated, return the memory to the free pool.
	{
		free(line_read);
		line_read = (char *)NULL;
	}
	line_read = readline("Enter a line: \n"); // in order to be able to compile, we have to add -lreadline flag to gcc
	if (line_read && *line_read) // if the line has any text in it, save it on the history
		add_history(line_read);
	return (line_read);
}

/*int	main()
{
	char	*line_read;
	char	*prompt;
	char	**line_splitted;
	int		i;

	i = 0;
	line_read = NULL;
	prompt = rl_gets(line_read);
	line_splitted = ft_split(prompt, ' ');
	while (line_splitted[i])
	{
		printf("lexer[%d] = %s\n", i, line_splitted[i]);
		i++;
	}
	return (0);
}*/