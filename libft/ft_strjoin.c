/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 16:46:29 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/06/07 18:43:26 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	char	*join_start;

	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	join = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!join)
		return (NULL);
	join_start = join;
	while (*s1)
	{
		*join = *s1;
		join++;
		s1++;
	}
	while (*s2)
	{
		*join = *s2;
		join++;
		s2++;
	}
	*join = '\0';
	return (join_start);
}

/*
int main(void)
{
	char str1[] = "Hello";
	char str2[] = "Bro";

	printf("Joined string is now: %s\n", ft_strjoin(str1, str2));
}
*/
