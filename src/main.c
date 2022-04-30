/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:03:14 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/04/30 13:00:07 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
	-> We can use 1 global variable. This should probably be the error code
*/

char	*rl_gets(char *line)
{
	if (line)
	{
		free(line);
		line = NULL;
	}
	line = readline("hm-0.1$ ");
	if (line && *line)
		add_history(line);
	return (line);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**tokens;

	(void)argc;
	(void)argv;
	(void)envp;
	line = NULL;
	while (1)
	{
		line = rl_gets(line);
		tokens = tokenize(line);
		print_tokens(tokens);
		expand_tokens(tokens);
		print_tokens(tokens);
		if (ft_strncmp(line, "clear history", 13) == 0)
			clear_history();
		rl_on_new_line();
	}
	return (0);
}
