/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toru <toru@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:20:54 by sataskin          #+#    #+#             */
/*   Updated: 2024/12/30 17:14:49 by toru             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* This function looks for the first occurrence of char c in the first bytes
n. It returns a pointer to the first occurrence or a NULL. */

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			index;
	unsigned char	*temp;
	unsigned char	u_c;

	temp = (unsigned char *)s;
	index = 0;
	u_c = (unsigned char)c;
	while (index < n)
	{
		if (temp[index] == u_c)
			return ((void *)&temp[index]);
		index++;
	}
	return (NULL);
}
