/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:29:55 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/07 13:55:53 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exec_pwd(void)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (!cwd)
		return (-1);
	ft_putstr_fd(cwd, g_cmd.scmds->fd_out.fd);
	write(g_cmd.scmds->fd_out.fd, "\n", 1);
	free (cwd);
	return (0);
}
