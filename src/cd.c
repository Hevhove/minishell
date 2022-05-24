/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:39:40 by mmaxime-          #+#    #+#             */
/*   Updated: 2022/05/24 14:10:01 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	set_pwd_vars_env(char *old_pwd, char *new_pwd, t_list **env)
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

static char	*get_new_cwd(char *tokens, t_list **env)
{
	char	*new_cwd;

	if (!tokens || (ft_strcmp(tokens, "~") == 0))
	{
		new_cwd = get_env_value("HOME", env);
		if (!new_cwd)
		{
			printf("HOME not set.\n");
			return (NULL);
		}
	}
	else if (ft_strcmp(tokens, "-") == 0)
	{
		new_cwd = get_env_value("OLDPWD", env);
		if (!new_cwd)
		{
			printf("OLDPWD not set.\n");
			return (NULL);
		}
	}
	else
		new_cwd = tokens;
	return (new_cwd);
}

int	exec_cd(char **tokens, t_list **env)
{
	char	*cwd;
	char	*new_cwd;

	(void)env;
	cwd = NULL;
	cwd = getcwd(cwd, 0);
	new_cwd = get_new_cwd(tokens[1], env);
	if (new_cwd == NULL)
		return (-1);
	if (chdir(new_cwd) != 0)
	{
		if (access(tokens[1], F_OK) != 0)
			printf("cd: %s: No such file or directory\n", tokens[1]);
		else if (access(tokens[1], X_OK) != 0)
			printf("cd: %s: Permission denied\n", tokens[1]);
		return (-1);
	}
	cwd = update_cwd(cwd);
	set_pwd_vars_env(cwd, new_cwd, env);
	//printf("new pwd = %s\n", new_cwd);
	return ;
}