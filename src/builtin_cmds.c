/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:02:52 by mmaxime-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/05/17 12:16:17 by hvan-hov         ###   ########.fr       */
=======
/*   Updated: 2022/05/17 13:51:01 by mmaxime-         ###   ########.fr       */
>>>>>>> 3ff64beaf7d3a9705de1fa01987570688f20c0a2
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

	cwd = getcwd(NULL, 0); // this can go to $OLDPWD in order to manage the cd -
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

	(void)tokens;
	// if (tokens[1])
	// {
	// 	printf("pwd: too many arguments\n");
	// 	return ;
	// }
	// if (tokens[1] && ft_strcmp(tokens[1], "|") == 0) -> exectute 2nd cmd
	cwd = getcwd(NULL, 0);
	printf("%s\n", cwd);
	return ;
}

void	exec_env(char **tokens, t_list **env)
{
	(void)tokens;
	// if (tokens[1])
	// {
	// 	printf("No option or argument allowed with this command\n");
	// 	return ;
	// }
	while (*env)
	{
		printf("%s\n", (*env)->content);
		env = &(*env)->next;
	}
}

int	exec_export(char **tokens, t_list **env)
{
	t_list	*new;

	if (!tokens[1])
	{
		export_no_var(env);
		return (0);
	}
	if (ft_isdigit((int)tokens[1][0]))
	{
		printf("bash: export: `%s': not a valid identifier\n", tokens[1]);
		return (-1);
	}
	if (!ft_strchr(tokens[1], '='))
		return (-1);
	new = ft_lstnew(tokens[1]);
	if (check_in_env(new, env) != 0)
		return (0);
	ft_lstadd_back(env, new);
	return (1);
}

// int main(int argc, char **argv, char **envp)
// {
// 	t_list	**env;

// 	(void)argc;
// 	env = (t_list **)malloc(sizeof(t_list));
// 	if (!env)
// 		return (1);
// 	*env = NULL;
// 	env_init(env, envp);
// 	exec_export(argv, env);
// 	exec_unset(argv, env);
// 	exec_env(argv, env);
// 	ft_clear_env(env);
// 	return (0);
// }
