/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:09:24 by mmaxime-          #+#    #+#             */
/*   Updated: 2022/05/23 19:13:22 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exec_cd(char **tokens)
{
	char	*cwd;
	char	*new_cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	new_cwd = get_new_cwd()
}