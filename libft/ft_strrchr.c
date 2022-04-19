/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 10:41:15 by mmaxime-          #+#    #+#             */
/*   Updated: 2021/11/02 10:46:38 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** SYNOPSIS : locate character in string
** LIBRARY : <string.h>
** DESC : The strrchr() function returns a pointer to
** the last occurrence of the character c in the string s.
*/

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	while (len >= 0 || c == '\0')
	{
		if (s[len] == (char)c)
			return ((char *)(s + len));
		len--;
	}
	return (0);
}
