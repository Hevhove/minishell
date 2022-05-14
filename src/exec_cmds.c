/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 13:35:49 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/05/14 15:23:02 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exec_cmds(t_cmd cmd)
{
	(void)cmd;
	// STEP 1: if heredoc of first scmd is 1, then open controls for heredoc

	// STEP 2: open files
	
	// STEP 3: open pipes

	// STEP 4: build the paths/envp to where to execute cmds
	// if no absolute path is given, execute relative path?

	// STEP 5: launch children for every pipe and execute either binaries or built-ins

	// STEP 6: close the pipes and fds, waitpid processes

	// STEP 7: free all the information used above, delete heredoc
}
