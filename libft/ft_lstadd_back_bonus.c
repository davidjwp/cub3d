/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:49:31 by djacobs           #+#    #+#             */
/*   Updated: 2022/12/02 10:49:36 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ilst;

	if (*lst == NULL)
		*lst = new;
	else
	{
		ilst = ft_lstlast(*lst);
		ilst->next = new;
	}
}
