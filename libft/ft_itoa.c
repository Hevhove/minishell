/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 10:36:09 by mmaxime-          #+#    #+#             */
/*   Updated: 2021/10/28 12:13:44 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** SYNOPSIS: convert integer to ASCII string
** LIBRARY: N/A
** DESC: Allocates (with malloc(3)) and returns a string representing the
** integer received as an argument. Negative numbers must be handled.
*/

#include "libft.h"

void	put_zero_or_minus(int n, char *result)
{
	if (n == 0)
		result[0] = '0';
	else if (n < 0)
		result[0] = '-';
}

int	len_n(int n)
{
	long	len;
	long	nbr;

	if (n < 1)
		len = 1;
	else
		len = 0;
	if (n < 0)
		nbr = -(long)n;
	else
		nbr = (long)n;
	while (nbr != 0)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	nbr;
	long	i;
	char	*result;

	i = len_n(n);
	result = (char *)malloc(sizeof(char) * (i + 1));
	if (result == NULL)
		return (0);
	result[i] = '\0';
	if (n < 0)
		nbr = -(long)n;
	else
		nbr = (long)n;
	while (i > 0)
	{
		result[i - 1] = nbr % 10 + 48;
		nbr /= 10;
		i--;
	}
	put_zero_or_minus(n, result);
	return (result);
}
