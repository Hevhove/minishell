/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:26:39 by mmaxime-          #+#    #+#             */
/*   Updated: 2021/11/02 10:30:06 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** SYNOPSIS : copy byte string
** LIBRARY : <string.h>
** DESC : The memmove() function copies len bytes from string src to string
** dst.  The two strings may overlap; the copy is always done in a non-
** destructive manner.
*/

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	const char	*csrc;
	char		*cdst;

	if (src < dst && src + len >= dst)
	{
		i = len;
		csrc = src;
		cdst = dst;
		while (i > 0)
		{
			cdst[i - 1] = csrc[i - 1];
			i--;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
