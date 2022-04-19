/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:53:49 by mmaxime-          #+#    #+#             */
/*   Updated: 2021/11/02 10:49:06 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** SYNOPSIS : locate character in string
** LIBRARY : <string.h>
** DESC : The strchr() function locates the first occurrence of
** c (converted to a char) in the string pointed to by s. The
** terminating null character is considered to be part of the
** string; therefore if c is `\0', the functions locate the
** terminating `\0'.
*/

/*#include "libft.h"*/

char	*ft_strchr(const char *s, int c)
{
	while (*s || c == '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (0);
}
