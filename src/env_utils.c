/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:07:14 by mmaxime-          #+#    #+#             */
/*   Updated: 2022/05/11 10:39:32 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int	array_len(char **array)
{
	int	len;

	len = 0;
	while (array[len])
		len++;
	return (len);
}

// void	get_env_table(char **env)
// {
// 	int	i;
// 	int	chars;

// }
