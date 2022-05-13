/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:02:52 by mmaxime-          #+#    #+#             */
/*   Updated: 2022/05/11 10:39:18 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

typedef struct	s_env
{
	char	*name;
	char	*value;
}	t_env;

void	exec_echo(char **tokens)
{
	int	i;
	
	if (!tokens[1])
	{
		printf("\n");
		return ;
	}
	i = 1;
	if (ft_strcmp(tokens[1], "-n") == 0)
		i = 2;
	while (tokens[i])
	{
		printf("%s", tokens[i]);
		if (tokens[i + 1])
			printf(" ");
		i++;
	}
	if (ft_strcmp(tokens[1], "-n") != 0)
		printf("\n");
}

void	exec_cd(char **tokens)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	printf("%s\n", cwd);
	if (!tokens[1] || (ft_strcmp(tokens[1], "~") == 0))
	{
		cwd = getenv("HOME");
		chdir(cwd);
	}
	else if (chdir(tokens[1]) != 0)
	{
		if (access(tokens[1], X_OK) != 0)
			printf("cd: %s: Permission denied\n", tokens[1]);
		else
			printf("cd: %s: No such file or directory\n", tokens[1]);
		return ;
	}
	cwd = getcwd(NULL, 0);
	printf("%s\n", cwd);
	return ;
}

void	exec_pwd(char **tokens)
{
	// to check why in bash: "pwd | cd .." does nothing while 
	// "pwd | ls" or "pwd | echo hello" works the way 2nd cmd is performed
	char	*cwd;
	// TAKE AWAY LATER:
	(void)tokens;

	// if (tokens[1] && ft_strcmp(tokens[1], "|") == 0) -> exectute 2nd cmd
	cwd = getcwd(NULL, 0);
	printf("%s\n", cwd);
	return ;
}

// void	exec_export(char **tokens)
// {
	
// }

// int main(int argc, char **argv)
// {
// 	exec_cd(argv);
// 	return (0);
// }
