/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:03:14 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/05/14 13:35:31 by hvan-hov         ###   ########.fr       */
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

int	main(void)
{
	char		*line;
	char		**tokens;
	t_cmd		cmd;

	line = NULL;
	while (1)
	{
		line = rl_gets(line);
		tokens = tokenize(line);
		if (!tokens)
			exit(3);
		expand_tokens(tokens);
		print_tokens(tokens);
		build_cmds(tokens, &cmd);
		exec_cmds(cmd);
		if (ft_strncmp(line, "clear history", 13) == 0)
			clear_history();
		free_tokens(tokens);
		free_cmds(cmd);
	}
	return (0);
}
