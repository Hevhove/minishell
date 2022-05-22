/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:03:14 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/05/22 17:33:48 by hvan-hov         ###   ########.fr       */
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

void	verify_tokens(char	**tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	char		**tokens;
	t_cmd		cmd;

	(void)argv;
	(void)argc;
	cmd.env = (t_list **)malloc(sizeof(t_list));
	if (!cmd.env)
		return (1);
	*(cmd.env) = NULL;
	tokens = NULL;
	env_init(cmd.env, envp);
	line = NULL;
	while (1)
	{
		line = rl_gets(line);
		tokens = tokenize(line);
		verify_tokens(tokens);
		// extra parsing steps to be done: start or end with pipe, only one heredoc allowed
		// token validity check on heredocs?
		if (!tokens)
			continue ; // or exit?
		expand_tokens(tokens);
		build_cmds(tokens, &cmd);
		build_paths(&cmd);
		exec_cmds(&cmd);
		free_tokens(tokens);
		free_cmds(cmd);
	}
	ft_clear_env(cmd.env);
	return (0);
}
