/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hendrik <Hendrik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:03:14 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/05/20 15:24:55 by Hendrik          ###   ########.fr       */
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
	//exec_env(cmd.env);
	line = NULL;
	while (1)
	{
		line = rl_gets(line);
		tokens = tokenize(line);
		// token validity check on heredocs?
		if (!tokens)
			continue ; // or exit?
		expand_tokens(tokens);
		//print_tokens(tokens);
		build_cmds(tokens, &cmd);
		build_paths(&cmd);
		exec_cmds(&cmd);
		if (ft_strncmp(line, "clear history", 13) == 0)
			clear_history();
		free_tokens(tokens);
		free_cmds(cmd);
		if (ft_strncmp(line, "exit", 4) == 0)
			break ;
	}
	ft_clear_env(cmd.env);
	printf("TESTINGXXXXXXX!\n");
	return (0);
}
