/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:39:40 by mmaxime-          #+#    #+#             */
/*   Updated: 2022/05/24 10:58:05 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	set_pwd_vars_env(char *old_pwd, char *new_pwd, t_list **env)
{
	char	*var_old_pwd;
	char	*var_pwd;
	t_list	*head;

	var_old_pwd = ft_strjoin("OLDPWD=", old_pwd);
	var_pwd = ft_strjoin("PWD=", new_pwd);
	head = *env;
	while (ft_strncmp((*env)->content, "OLDPWD=", 7) != 0)
		*env = (*env)->next;
	(*env)->content = var_old_pwd;
	*env = head;
	while (ft_strncmp((*env)->content, "PWD=", 4) != 0)
		*env = (*env)->next;
	(*env)->content = var_pwd;
	*env = head;
	ft_free(&var_old_pwd);
	ft_free(&var_pwd);
	exec_env(env);
	return ;
}

void	exec_cd(char **tokens, t_list **env)
{
	char	*cwd;
	char	*new_cwd;

	(void)env;
	cwd = getcwd(NULL, 0);
	//printf("old_pwd = %s\n", cwd);
	if (!tokens[1] || (ft_strcmp(tokens[1], "~") == 0))
	{
		cwd = getenv("HOME");
		chdir(cwd);
	}
	//else if (ft_strcmp(tokens[1], "-") == 0) -> = cd OLDPWD
	else if (chdir(tokens[1]) != 0)
	{
		if (access(tokens[1], F_OK) != 0)
			printf("cd: %s: No such file or directory\n", tokens[1]);
		else if (access(tokens[1], X_OK) != 0)
			printf("cd: %s: Permission denied\n", tokens[1]);
		return ;
	}
	new_cwd = getcwd(NULL, 0);
	set_pwd_vars_env(cwd, new_cwd, env);
	//printf("new pwd = %s\n", new_cwd);
	return ;
}