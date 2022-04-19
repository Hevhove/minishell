/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 13:12:25 by mmaxime-          #+#    #+#             */
/*   Updated: 2021/10/28 17:09:43 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** SYNOPSIS : find lenght of string
** LIBRARY : <string.h>
** DESC : The strlen() function computes the length of the
** string s.  The strnlen() function attempts to compute
** the length of s, but never scans beyond the first
** maxlen bytes of s.
*/

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}
