/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:55:13 by djacobs           #+#    #+#             */
/*   Updated: 2022/11/30 18:40:21 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*templst;

	newlst = NULL;
	if (!lst)
		return (NULL);
	while (lst && f && del)
	{
		templst = ft_lstnew((*f)(lst->content));
		if (!templst)
			ft_lstclear(&templst, (*del));
		else
			ft_lstadd_back(&newlst, templst);
		lst = lst->next;
	}
	return (newlst);
}
