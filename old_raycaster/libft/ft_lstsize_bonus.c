/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 15:51:13 by djacobs           #+#    #+#             */
/*   Updated: 2022/11/26 19:22:04 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		lstsize;
	t_list	*plst;

	plst = lst;
	lstsize = 0;
	while (plst)
	{
		plst = plst->next;
		lstsize++;
	}
	return (lstsize);
}
