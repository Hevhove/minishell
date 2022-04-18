/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_read_dir_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miam <miam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:16:38 by mmaxime-          #+#    #+#             */
/*   Updated: 2022/04/13 16:31:17 by miam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

int	main(int argc, char **argv)
{
	DIR				*dir;
	struct dirent	*sd;
	
	dir = opendir(".");
	if (dir == NULL)
	{
		printf("Error! Unable to open directory... \n");
		exit(1);
	}
	sd = readdir(dir);
	while (sd != NULL) // in order to read all elements from the directory one by one --> can be the behaviour of ls command
	{
		printf(">> %s\n", sd->d_name);
		sd = readdir(dir);
	}
	closedir(dir);
	return (0);
}