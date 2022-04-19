/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 10:38:52 by mmaxime-          #+#    #+#             */
/*   Updated: 2021/10/28 11:24:00 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** SYNOPSIS : duplicate a string
** LIBRARY : <string.h>
** DESC : The  strdup() function returns a pointer to
** a new string which is a duplicate of the string s.
** Memory for the new string  is  obtained  with
** malloc(3), and can be freed with free(3).
*/

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dst;
	size_t	len;

	len = ft_strlen(s) + 1;
	dst = (char *)malloc(len);
	if (dst == NULL)
		return (0);
	ft_memcpy(dst, s, len);
	return (dst);
}
