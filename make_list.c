/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walnaimi <walnaimi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:46:29 by sataskin          #+#    #+#             */
/*   Updated: 2025/01/09 14:08:24 by walnaimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_input(t_minirt *rt)
{
	t_arg	*test;
	int		a;
	int		c;
	int		l;

	a = 0;
	c = 0;
	l = 0;
	test = rt->l_list;
	while (test != NULL)
	{
		if (test->a == 1)
			a = 1;
		if (test->c == 1)
			c = 1;
		if (test->l == 1)
			l = 1;
		test = test->next;
	}
	if (a == 0 || c == 0 || l == 0)
		free_minirt(rt, "Error: Invalid Input You traitor\n");
}

void	ft_lstadd_back_rt(t_arg **lst, t_arg *new)
{
	t_arg	*node;

	node = *lst;
	if (!new)
		return ;
	else if (*lst == NULL)
		*lst = new;
	else
	{
		while (node->next != NULL)
			node = node->next;
		node->next = new;
	}
}
