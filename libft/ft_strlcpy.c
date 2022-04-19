/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:02:33 by mmaxime-          #+#    #+#             */
/*   Updated: 2021/11/02 15:15:27 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** SYNOPSIS : size-bounded string copying
** LIBRARY : <string.h>
** DESC : The strlcpy() function copy strings with the same input
** parameters and output result as snprint(3).
** It takes the full size of the destination buffer and guarantee
** NUL-termination if there is room. Note that room for the NUL
** should be included in dstsize.
** strlcpy() copies up to dstsize - 1 characters from the string
** src to dst, NUL-terminating the result if dstsize is not 0.
*/

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srcsize;
	size_t	i;

	if (!dst || !src)
		return (0);
	srcsize = ft_strlen(src);
	i = 0;
	if (dstsize != 0)
	{
		while (src[i] && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srcsize);
}
