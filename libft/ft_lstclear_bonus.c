/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:09:01 by sataskin          #+#    #+#             */
/*   Updated: 2023/11/14 17:17:01 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*clr;

	if (!*lst || !del)
		return ;
	while (*lst)
	{
		clr = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = clr;
	}
	*lst = NULL;
}
