/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:29:44 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/05/23 19:30:23 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
