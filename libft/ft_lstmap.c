/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 11:08:43 by mmaxime-          #+#    #+#             */
/*   Updated: 2021/11/01 13:04:19 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** SYNOPSIS: apply function to content of all list's elements into new list
** LIBRARY: N/A
** DESC: Iterates the list ’lst’ and applies the function ’f’ to the content of
** each element. Creates a new list resulting of the successive applications of
** the function ’f’. The ’del’ function is used to delete the content of an
** element if needed.
*/

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*element;
	t_list	*new_lst;

	if (!lst)
		return (0);
	new_lst = 0;
	while (lst)
	{
		element = ft_lstnew((*f)(lst->content));
		if (!element)
		{
			ft_lstclear(&new_lst, (*del));
			return (0);
		}
		ft_lstadd_back(&new_lst, element);
		lst = lst->next;
	}
	return (new_lst);
}
